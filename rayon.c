#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pgm.h"
#include "fichierRondelle.h"
#include "histogramme.h"

#define MAX 50

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
 * @brief Calcule et renvoie la largeur de la rondelle
 * 
 * @param seuil le seuil entre pixels blancs et noirs
 */
int getLargeurRondelle(int **rondelle, int longueur, int hauteur, int seuil)
{
	int rayon = 0;

	size_t i = 0;
	size_t j = 0;

	while (rondelle[i][j] > seuil && j < longueur)
	{
		j++;
	}

	while (rondelle[i][j] < seuil && i < hauteur)
	{
		i++;
		rayon++;
	}

	return rayon;
}

/**
 * @brief Calcule et renvoie le diamètre du cercle intérieur (vide) de la rondelle
 * 
 * @param largeurRondelle la largeur de la rondelle
 * @param seuil le seuil entre pixels blancs et noirs
 */
int getDiametreInterieur(int **rondelle, int longueur, int hauteur, int largeurRondelle, int seuil)
{
	int diametre = 0;

	size_t i = largeurRondelle;
	size_t j = largeurRondelle * 2 - 1;

	while (rondelle[i][j] > seuil && i < hauteur - largeurRondelle)
	{
		i++;
		diametre++;
	}

	return diametre;
}

/**
 * @brief 
 * 
 * @param rondelle 
 * @param longueur 
 * @param hauteur 
 * @param seuil 
 * @return int 
 * 0 - la rondelle n'a pas de défauts
 * 1 - la rondelle a de mauvaises dimensions
 * 2 - la rondelle a un défaut
 */
int rondelleEstDefectueuse(int **rondelle, int longueur, int hauteur, int seuil)
{
	int estDefectueuse = 0;

	int largeurRondelle = getLargeurRondelle(rondelle, longueur, hauteur, seuil);

	if (largeurRondelle != 17)
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

int main(int argc, char const *argv[])
{
	PGMValeurs *fichier = NULL;
	int **rondelle = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/3/defect_";
		char c[10];
		sprintf(c, "%d", i);
		strcat(chemin_fich, c);
		strcat(chemin_fich, ".pgm");
		printf("\n%s\n", chemin_fich);

		char chemin_rond[MAX] = "rondelle/r_";
		strcat(chemin_rond, c);
		strcat(chemin_rond, ".pgm");
		printf("%s\n", chemin_rond);

		PGMValeurs *fichier = getPGMfile(chemin_fich);
		int longueur, hauteur;

		int seuil = getSeuil(construitHistogramme(fichier));

		int **rondelle = construitRondelle(fichier, &longueur, &hauteur, seuil);

		sauvegarderRondelle(chemin_rond, (const int **)rondelle, longueur, hauteur);

		int defaut = rondelleEstDefectueuse(rondelle, longueur, hauteur, seuil);

		switch (defaut)
		{
		case 0:
			printf("La rondelle n'est pas défectueuse.\n");
			break;

		case 1:
			printf("La rondelle a un défaut de dimension.\n");
			break;

		case 2:
			printf("La rondelle a un défaut de surface.\n");
			break;

		default:
			printf("ERREUR: rondelleEstDefectueuse\n");
			break;
		}
	}

	free(rondelle);
	free(fichier);

	return 0;
}
