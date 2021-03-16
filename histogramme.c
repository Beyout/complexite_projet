#include <string.h>
#include <math.h>
#include "pgm.h"
#include "fichierRondelle.h"

#define MAX 50
#define NB_INTERVALLES 32
#define DIVISEUR 256 / NB_INTERVALLES

int *construitHistogramme(PGMValeurs *fichier)
{
	int *histogramme = malloc(sizeof(int) * NB_INTERVALLES);

	for (int i = 0; i < NB_INTERVALLES; i++)
	{
		histogramme[i] = 0;
	}

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			int index = floor(fichier->valeurs[i][j] / (DIVISEUR));
			histogramme[index]++;
		}
	}

	return histogramme;
}

int getIndexMin(int *histogramme)
{
	int min = 0;

	for (size_t i = 1; i < NB_INTERVALLES; i++)
	{
		if (histogramme[i] < histogramme[min])
		{
			min = i;
		}
	}

	return min;
}

int getSeuil(int *histogramme)
{
	int min = histogramme[getIndexMin(histogramme)] + 10;
	printf("min: %d\n", min);

	int inf10Bas = -1;
	int inf10Haut = -1;

	size_t i = 0;
	while (inf10Bas == -1 && i < NB_INTERVALLES)
	{
		if (histogramme[i] < min)
		{
			inf10Bas = (int)i;
		}
		i++;
	}

	while (histogramme[i] < min && i < NB_INTERVALLES)
	{
		i++;
	}

	inf10Haut = i;

	return (int)((inf10Bas + inf10Haut) / 2) * (DIVISEUR);
}

void dessineHistogramme(PGMValeurs *fichier)
{
	int *tab = construitHistogramme(fichier);

	for (int i = 0; i < NB_INTERVALLES; i++)
	{
		char *str = (char *)malloc(9 * sizeof(char));
		int borneInf = (DIVISEUR)*i;
		sprintf(str, "[%3d-%3d[", borneInf, (DIVISEUR) * (i + 1));
		printf("%s %6d\n", str, tab[i]);
		free(str);
	}
	free(tab);
}

int main(int argc, char const *argv[])
{
	// char *chemin_fich = "dataset/3/defect_1.pgm";
	// dessineHistogramme(chemin_fich);

	PGMValeurs *fichier;


	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/3/defect_";
		char c[10];
		sprintf(c, "%d", i);
		strcat(chemin_fich, c);
		strcat(chemin_fich, ".pgm");
		printf("\n%s\n", chemin_fich);

		fichier = getPGMfile(chemin_fich);

		int *tab = construitHistogramme(fichier);
		int seuil = getSeuil(tab);
		free(tab);

		int longueur, hauteur;
		int **rondelle = construitRondelle(fichier, &longueur, &hauteur);

		for (size_t i = 0; i < hauteur; i++)
		{
			for (size_t j = 0; j < longueur; j++)
			{
				if (rondelle[i][j] < seuil)
				{
					printf("NNN");
				}
				else
				{
					printf("   ");
				}
			}
			printf("\n");
		}

		printf("fin fichier\n");
	}

	free(fichier);

	return 0;
}
