#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Sauvegarde la rondelle dans le fichier "rondelle.pgm"
 * 
 * @param rondelle le tableau de la rondelle que l'on veut sauvegarder
 */
void sauvegarderRondelle(const int **rondelle, const int longueur, const int hauteur)
{
	FILE *destination;
	destination = fopen("rondelle.pgm", "w");
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
void getDimensionsRondelle(PGMValeurs fichier, int *longueur, int *hauteur, int *xmin, int *ymin, int *xmax, int *ymax)
{
	*xmin = 512;
	*ymin = 512;
	*xmax = 0;
	*ymax = 0;

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			if (fichier.valeurs[i][j] < 48)
			{
				if (j < *xmin)
				{
					*xmin = j;
				}
				else if (j > *xmax)
				{
					*xmax = j;
				}

				if (i < *ymin)
				{
					*ymin = i;
				}
				else if (i > *ymax)
				{
					*ymax = i;
				}
			}
		}
	}

	*longueur = (*xmax - *xmin) + 1;
	*hauteur = (*ymax - *ymin) + 1;
}

/**
 * @brief Construit et retourne le tableau d'entiers rondelle, représentant la rondelle dans un carré.
 * Modifie les entiers longueur et hauteur qui sont les dimensions de la rondelle, 
 * ceci est utile car il n'y a pas d'autres moyens de connaître les dimensions de la rondelle autrement
 * 
 * @param fichier le fichier que l'on parcourt
 * @param longueur la longueur de la rondelle
 * @param hauteur l'hauteur de la rondelle
 */
int **construitRondelle(PGMValeurs fichier, int *longueur, int *hauteur)
{
	int xmin, ymin, xmax, ymax;

	getDimensionsRondelle(fichier, longueur, hauteur, &xmin, &ymin, &xmax, &ymax);

	// Initialisation de la rondelle
	int **rondelle = (int **)malloc(*hauteur * sizeof(*rondelle));

	for (int i = 0; i <= *hauteur; i++)
	{
		rondelle[i] = (int *)malloc(*longueur * sizeof(**rondelle));
	}

	// Construction de la rondelle
	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			int px = fichier.valeurs[y][x];
			rondelle[y - ymin][x - xmin] = px;
		}
	}

	return rondelle;
}