#include <stdio.h>
#include <stdlib.h>

#define MAX_RONDELLES 64
#define SEUIL 96

/**
 * @brief Sauvegarde la rondelle dans le fichier "rondelle.pgm"
 * 
 * @param rondelle le tableau de la rondelle que l'on veut sauvegarder
 */
void sauvegarderRondelle(char *chemin, const int **rondelle, const int longueur, const int hauteur)
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

void getDimensionsRondelleUnique(PGMValeurs *fichier, int x, int y, int seuil, int *longueur, int *hauteur, int *largeur)
{
	*largeur = 0;

	while (fichier->valeurs[y][x] < seuil)
	{
		*largeur += 1;
		y++;
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

void scanPortion(PGMValeurs *fichier, int seuil, int x, int y, int xmax, int ymax, int *longueur, int *hauteur, int *largeur, int *tabX, int *tabY, int *nRondelles)
{
	int i = x;
	int j = y;

	while (j < ymax)
	{
		while (i < xmax)
		{
			if (fichier->valeurs[j][i] < seuil)
			{
				int estDejaTrouve = 0;
				for (size_t i = 0; i < *nRondelles; i++)
				{
					int xmin = tabX[i] - (largeur[i] - 1) * 2;
					int xmax = tabX[i] + (largeur[i] - 1) * 2;
					int ymin = tabY[i];
					int ymax = tabY[i] + hauteur[i] - 1;

					if (j < ymax && j > ymin && x < xmax && x > xmin)
					{
						estDejaTrouve = 1;
					}
				}

				if (estDejaTrouve != 1)
				{
					*nRondelles++;

					int l, h, larg;

					getDimensionsRondelleUnique(fichier, i, j, seuil, &l, &h, &larg);

					longueur[*nRondelles] = l;
					hauteur[*nRondelles] = h;
					largeur[*nRondelles] = larg;
					tabX[*nRondelles] = j;
					tabY[*nRondelles] = i;

					if (i - (larg - 1) * 2 > 0)
					{
						scanPortion(fichier, seuil, 0, y, i - (larg - 1) * 2, y + hauteur[*nRondelles], longueur, hauteur, largeur, tabX, tabY, nRondelles);
					}
					if (i + (larg - 1) * 2 < xmax)
					{
						scanPortion(fichier, seuil, i + (larg - 1), y, 512, y + hauteur[*nRondelles] - 1, longueur, hauteur, largeur, tabX, tabY, nRondelles);
					}
				}
			}

			i++;
		}
		i = x;
		j++;
	}
}

int getMax(int *tab)
{
	int max = -1;
	int tmp = -1;

	for (size_t i = 0; i < sizeof(tab); i++)
	{
		if (tab[i] > tmp)
		{
			tmp = tab[i];
			max = i;
		}
	}

	return max;
}

/**
 * @brief Obtient les dimensions de la rondelle
 * 
 * @param fichier le fichier que l'on parcourt
 * @param longueur la longueur que l'on va modifier
 * @param hauteur l'hauteur que l'on va modifier
 * @param xmin la pointe nord de la rondelle
 * @param ymin la pointe ouest de la rondelle
 * @param xmax la pointe sud de la rondelle
 * @param ymax la pointe est de la rondelle
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

				for (size_t i = 0; i < nRondelles; i++)
				{
					int xmin = tabX[i] - (largeur[i]) * 2;
					int xmax = tabX[i] + (largeur[i]) * 2;
					int ymin = tabY[i];
					int ymax = tabY[i] + hauteur[i];

					if (y < ymax && y > ymin && x < xmax && x > xmin)
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
 * Modifie les entiers longueur et hauteur qui sont les dimensions de la rondelle, 
 * ceci est utile car il n'y a pas d'autres moyens de connaître les dimensions de la rondelle autrement
 * 
 * @param fichier le fichier que l'on parcourt
 * @param longueur la longueur de la rondelle
 * @param hauteur la hauteur de la rondelle
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