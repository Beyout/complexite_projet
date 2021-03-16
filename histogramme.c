#include <math.h>
#include "pgm.h"

void construitHistogramme(int *histogramme, char *chemin)
{
	PGMValeurs *fichier = getPGMfile(chemin);

	for (int i = 0; i < 32; i++)
	{
		histogramme[i] = 0;
	}

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			int index = floor(fichier->valeurs[i][j] / 8);
			histogramme[index]++;
		}
	}

	free(fichier);
}

void dessineHistogramme(char *chemin)
{
	int tab[32];
	construitHistogramme(tab, chemin);
	for (int i = 0; i < 32; i++)
	{
		char *str = (char *)malloc(9 * sizeof(char));
		sprintf(str, "[%3d-%3d[", 8 * i, 8 * (i + 1));
		printf("%s %6d\n", str, tab[i]);
		free(str);
	}
}

int main(int argc, char const *argv[])
{
	dessineHistogramme("dataset/3/defect_0.pgm");
	return 0;
}
