#include <stdio.h>
#include <time.h>
#include <math.h>

#include "headers/pgm.h"
#include "headers/fichierRondelle.h"
#include "headers/histogramme.h"
#include "headers/traitementRondelle.h"

#define MAX 50

/**
 * @brief Lance l'analyse du fichier passé en paramètre, sert à afficher le csv
 */
void analyse(PGMValeurs *fichier, const char *nomFich, int ***rondelles, int *longueur, int *hauteur, int *largeur, int nRondelles, int seuil, clock_t debut, clock_t fin)
{
	printf("%s,", nomFich);

	int estRefuse = 0;

	for (int i = 0; i < nRondelles; i++)
	{
		// DETECTION DEFAUTS
		int defaut = rondelleEstDefectueuse(rondelles[i], longueur[i], hauteur[i], largeur[i], seuil);

		if (defaut > 0)
			estRefuse = 1;
	}

	if (estRefuse == 0)
	{
		printf("accepté,");
	}
	else
	{
		printf("refusé,");
	}

	fin = clock();

	double tps = ((double)fin - debut) / CLOCKS_PER_SEC;

	printf("%1.3lf\n", tps);
}

/**
 * @brief Fonction de Reporting
 */
void report(PGMValeurs *fichier, const char *nomFich, int ***rondelles, int *longueur, int *hauteur, int *largeur, int nRondelles, int seuil, clock_t debut, clock_t fin)
{
	printf("fichier: %s\n", nomFich);

	int anneauxDefectueux = 0;

	for (int i = 0; i < nRondelles; i++)
	{
#ifdef SAVE
		// SAUVEGARDE
		char chemin_rond[50] = "rondelle/r_";
		char tmp[10];
		sprintf(tmp, "%d", i);
		strcat(chemin_rond, tmp);
		strcat(chemin_rond, ".pgm");
		printf("sauvegarde: %s\n", chemin_rond)
			sauvegarderRondelle(chemin_rond, (const int **)rondelles[i], longueur[i], hauteur[i], seuil);
#endif

		// DETECTION DEFAUTS
		int defaut = rondelleEstDefectueuse(rondelles[i], longueur[i], hauteur[i], largeur[i], seuil);

		switch (defaut)
		{
		case 0:
			printf("La rondelle %d n'est pas défectueuse.\n", i + 1);
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

		if (defaut > 0)
			anneauxDefectueux++;
	}

	if (anneauxDefectueux > 0)
	{
		printf("Le fichier contient des rondelles défectueuses (%d rondelles sur %d rondelles) !\n", anneauxDefectueux, nRondelles);
	}
	else
	{
		printf("Le fichier ne contient que des rondelles valides (nombre de rondelles: %d) !\n", nRondelles);
	}
}

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		clock_t debut;
		clock_t fin;

		debut = clock();
		PGMValeurs *fichier = getPGMfile(argv[1]);

		int longueur[MAX_RONDELLES];
		int hauteur[MAX_RONDELLES];
		int largeur[MAX_RONDELLES];
		int nRondelles;

		int seuil = getSeuil(construitHistogramme(fichier));

		int ***rondelles = construitRondelles(fichier, longueur, hauteur, largeur, seuil, &nRondelles);

#ifndef REPORT
		analyse(fichier, argv[1], rondelles, longueur, hauteur, largeur, nRondelles, seuil, debut, fin);
#endif

#ifdef REPORT
		report(fichier, argv[1], rondelles, longueur, hauteur, largeur, nRondelles, seuil, debut, fin);
#endif

		free(rondelles);
		free(fichier);
	}
	else
		printf("Veuillez spécifier un et un seul fichier !\n");

	return 0;
}
