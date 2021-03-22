#include <stdio.h>
#include <stdlib.h>

#define MAX_RONDELLES 64

/**
 * @brief Sauvegarde la rondelle dans le fichier "rondelle.pgm"
 * 
 * @param rondelle le tableau de la rondelle que l'on veut sauvegarder
 */
void sauvegarderRondelle(char *chemin, const int **rondelle, const int longueur, const int hauteur, int seuil)
{
	FILE *destination;
	destination = fopen(chemin, "w");
	fprintf(destination, "P5\n");
	fprintf(destination, "%d %d\n", longueur, hauteur);
	fprintf(destination, "255\n");

	for (int y = 0; y < hauteur; y++)
	{
		for (int x = 0; x < longueur; x++)
		{
			int px = rondelle[y][x];
			putc(px, destination);
		}
	}
	fprintf(destination, "\n");
	fclose(destination);
}

/**
 * @brief Cherche les dimensions d'une rondelle et les stock dans différents tableaux
 * 
 * @param x la coordonnée X de la rondelle
 * @param y la coordonnée Y de la rondelle
 */
void getDimensionsRondelleUnique(PGMValeurs *fichier, int x, int y, int seuil, int *longueur, int *hauteur, int *largeur)
{
	*largeur = 0;

	while (fichier->valeurs[y][x] < seuil || *largeur < 17)
	{
		*largeur += 1;
		y++;
	}

	while (fichier->valeurs[y - 1][x] > seuil)
	{
		y--;
		*largeur -= 1;
	}

	int diametreInt = 0;

	while (fichier->valeurs[y][x] > seuil)
	{
		diametreInt++;
		y++;
	}

	*longueur = 2 * (*largeur) + diametreInt;
	*hauteur = 2 * (*largeur) + diametreInt;
}

/**
 * @brief Obtient les dimensions des rondelles
 * 
 * @param fichier le fichier que l'on parcourt
 * @param tabX les coordonnées X des rondelles, utile pour les construire ensuite
 * @param tabY les coordonnées Y des rondelles, utile pour les construire ensuite
 * 
 */
int getDimensionsRondelles(PGMValeurs *fichier, int *longueur, int *hauteur, int *largeur, int *tabX, int *tabY, int seuil)
{
	int nRondelles = 0;

	int x = 0;
	int y = 0;

	while (y < 512)
	{
		while (x < 512)
		{
			if (fichier->valeurs[y][x] < seuil)
			{
				int estDejaTrouve = 0;
				int xmin, xmax, ymin, ymax;

				for (size_t i = 0; i < nRondelles; i++)
				{
					xmin = tabX[i] - largeur[i] - (hauteur[i] - 2 * largeur[i]) / 2;
					xmax = tabX[i] + (largeur[i]) + (hauteur[i] - 2 * largeur[i]) / 2;
					ymin = tabY[i];
					ymax = tabY[i] + hauteur[i];

					if (y <= ymax && y >= ymin && x <= xmax && x >= xmin)
					{
						estDejaTrouve = 1;
					}
				}

				if (estDejaTrouve != 1)
				{
					int l, h, larg;

					getDimensionsRondelleUnique(fichier, x, y, seuil, &l, &h, &larg);

					longueur[nRondelles] = l;
					hauteur[nRondelles] = h;
					largeur[nRondelles] = larg;
					tabX[nRondelles] = x;
					tabY[nRondelles] = y;

					nRondelles++;
				}
			}

			x++;
		}
		x = 0;
		y++;
	}

	return nRondelles;
}

/**
 * @brief Construit et renvoie une rondelle
 * 
 * @return int** la rondelle
 */
int **construitRondelleUnique(PGMValeurs *fichier, int longueur, int hauteur, int xmin, int xmax, int ymin, int ymax)
{
	int **rondelle = (int **)calloc(hauteur, sizeof(*rondelle));

	for (int i = 0; i <= hauteur; i++)
	{
		rondelle[i] = (int *)calloc(longueur, sizeof(int));
	}

	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			int px = fichier->valeurs[y][x];
			rondelle[y - ymin][x - xmin] = px;
		}
	}

	return rondelle;
}

/**
 * @brief Construit et retourne un tableau à 3 dimensions de rondelles, chaque rondelle étant un tableau à 2 dimensions.
 * Ajoute les longueurs, hauteurs et largeurs des rondelles. 
 * Ceci est utile car il n'y a pas d'autres moyens de connaître les dimensions de la rondelle autrement
 * 
 * @param fichier le fichier que l'on parcourt
 * @param longueur les longueurs des rondelles
 * @param hauteur les hauteur des rondelles
 * @param largeur les largeurs des rondelles
 */
int ***construitRondelles(PGMValeurs *fichier, int *longueur, int *hauteur, int *largeur, int seuil, int *nRondelles)
{
	int tabX[MAX_RONDELLES];
	int tabY[MAX_RONDELLES];

	*nRondelles = getDimensionsRondelles(fichier, longueur, hauteur, largeur, tabX, tabY, seuil);

	// Initialisation de la rondelle
	int ***rondelles = (int ***)calloc(*nRondelles, sizeof(***rondelles));

	for (int i = 0; i < *nRondelles; i++)
	{
		rondelles[i] = (int **)calloc(hauteur[i], sizeof(**rondelles));

		for (int j = 0; j <= *hauteur; j++)
		{
			rondelles[i][j] = (int *)calloc(longueur[i], sizeof(int));
		}
	}

	// Construction de la rondelle
	for (int i = 0; i < *nRondelles; i++)
	{
		int xmin = tabX[i] - (largeur[i] - 1) * 2;
		int xmax = tabX[i] + (largeur[i] - 1) * 2;
		int ymin = tabY[i];
		int ymax = tabY[i] + hauteur[i] - 1;

		int **r = construitRondelleUnique(fichier, longueur[i], hauteur[i], xmin, xmax, ymin, ymax);
		rondelles[i] = r;
	}

	return rondelles;
}