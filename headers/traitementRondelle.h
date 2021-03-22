#include <stdio.h>
#include <string.h>

/**
 * @brief Nombre de pixels noirs constituants la rondelle.
 */
#define SOMME_PIXELS_NOIRS 2416

/**
 * @brief Calcule et renvoie le nombre de pixels noirs constituants la rondelle
 * 
 * @param seuil le seuil entre pixels blancs et noirs
 */
int getNPixelsNoirs(int **rondelle, int longueur, int hauteur, int seuil)
{
	int sum = 0;
	for (size_t i = 0; i < hauteur; i++)
	{
		for (size_t j = 0; j < longueur; j++)
		{
			if (rondelle[i][j] < seuil)
			{
				sum++;
			}
		}
	}

	return sum;
}

/**
 * @brief 
 * @return int 
 * 0 - la rondelle n'a pas de défauts
 * 1 - la rondelle a de mauvaises dimensions
 * 2 - la rondelle a un défaut
 */
int rondelleEstDefectueuse(int **rondelle, int longueur, int hauteur, int largeur, int seuil)
{
	int estDefectueuse = 0;

	if (largeur != 17)
	{
		estDefectueuse = 1;
	}
	else
	{
		int nPixelsNoirs = getNPixelsNoirs(rondelle, longueur, hauteur, seuil);

		if (nPixelsNoirs != SOMME_PIXELS_NOIRS)
		{
			estDefectueuse = 2;
		}
	}

	return estDefectueuse;
}