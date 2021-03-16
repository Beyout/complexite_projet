#include <stdio.h>
#include <string.h>
#include "pgm.h"
#include "fichierRondelle.h"

#define MAX 50

int getRayonExterieur(PGMValeurs *fichier, int **rondelle, int longueur, int hauteur)
{
	int rayon = 0;

	size_t i = 0;
	size_t j = 0;

	while (rondelle[i][j] > 48 && j < longueur)
	{
		j++;
	}

	while (rondelle[i][j] < 48 && i < hauteur)
	{
		i++;
		rayon++;
	}

	return rayon;
}

int getRayonInterieur(PGMValeurs *fichier, int **rondelle, int longueur, int hauteur, int rayonExterieur)
{
	int rayon = 0;

	size_t i = rayonExterieur;
	size_t j = rayonExterieur * 2 - 1;

	while (rondelle[i][j] > 48 && i < hauteur - rayonExterieur)
	{
		i++;
		rayon++;
	}

	return rayon;
}

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/2/radius_";
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

		int **rondelle = construitRondelle(*fichier, &longueur, &hauteur);

		sauvegarderRondelle(chemin_rond, (const int **)rondelle, longueur, hauteur);

		int rayonExterieur = getRayonExterieur(fichier, rondelle, longueur, hauteur);
		int rayonInterieur = getRayonInterieur(fichier, rondelle, longueur, hauteur, rayonExterieur);
		printf("rayonExt: %d\n", rayonExterieur);
		printf("rayonInt: %d\n", rayonInterieur);

		free(rondelle);
		free(fichier);
	}

	return 0;
}
