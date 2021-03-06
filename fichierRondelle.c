#include <stdio.h>
#include "pgm.h"

void sauvegarderRondelle(int longueur, int hauteur, int rondelle[hauteur][longueur])
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

void construitRondelle(PGMValeurs fichier, int longueur, int hauteur, int rondelle[hauteur][longueur], int xmin, int ymin, int xmax, int ymax)
{
	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{

			int px = fichier.valeurs[y][x];
			rondelle[y - ymin][x - xmin] = px;
		}
	}
}

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

int main(int argc, char const *argv[])
{
	int longueur, hauteur, xmin, ymin, xmax, ymax;
	char *chemin = "dataset/1/single_0.pgm";

	PGMValeurs *fichier = malloc(sizeof(PGMValeurs));
	getPGMfile(chemin, fichier);

	getDimensionsRondelle(*fichier, &longueur, &hauteur, &xmin, &ymin, &xmax, &ymax);
	int rondelle[hauteur][longueur];

	construitRondelle(*fichier, longueur, hauteur, rondelle, xmin, ymin, xmax, ymax);

	// sauvegarderRondelle(longueur, hauteur, rondelle);

	free(fichier);
	return 0;
}
