#include <string.h>
#include <math.h>

/**
 * @brief Nombre d'intervalles pour l'histogramme
 */
#define NB_INTERVALLES 32

/**
 * @brief Taille de l'ensemble d'un intervalle
 */
#define DIVISEUR 256 / NB_INTERVALLES

/**
 * @brief Construit l'histogramme et le renvoie
 * 
 * @param fichier le fichier pour lequel il faut construire l'histogramme
 */
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

/**
 * @brief Retourne l'index du plus petit intervalle
 * 
 * @param histogramme l'histogramme qu'il faut analyser
 */
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

/**
 * @brief Calcule le seuil entre pixels blancs et noirs de l'histogramme
 * @return int le seuil
 */
int getSeuil(int *histogramme)
{
	int min = histogramme[getIndexMin(histogramme)] + 10;

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

/**
 * @brief Dessine l'histogramme du fichier passé en paramètre
 */
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