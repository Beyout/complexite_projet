#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "headers/pgm.h"
#include "headers/fichierRondelle.h"
#include "headers/histogramme.h"
#include "headers/traitementRondelle.h"

#define MAX 50

void test(char *chemin_fich, int index, int ***rondelles, int assertion)
{
	char c[10];
	sprintf(c, "%d", index);
	strcat(chemin_fich, c);
	strcat(chemin_fich, ".pgm");
	printf("%s\n", chemin_fich);

	PGMValeurs *fichier = getPGMfile(chemin_fich);
	int longueur[MAX_RONDELLES];
	int hauteur[MAX_RONDELLES];
	int largeur[MAX_RONDELLES];
	int nRondelles;
	int seuil = getSeuil(construitHistogramme(fichier));

	rondelles = construitRondelles(fichier, longueur, hauteur, largeur, seuil, &nRondelles);

	int estDefectueuse = 0;

	for (int j = 0; j < nRondelles; j++)
	{
		// DETECTION DEFAUTS
		int defaut = rondelleEstDefectueuse(rondelles[j], longueur[j], hauteur[j], largeur[j], seuil);

		if (defaut > 0)
		{
			estDefectueuse = 1;
		}
	}

	assert(estDefectueuse == assertion);

	printf("\n");
}

void testsSingle()
{
	PGMValeurs *fichier = NULL;
	int ***rondelles = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/1/single_";

		test(chemin_fich, i, rondelles, 0);

		free(rondelles);

		printf("\n");
	}

	free(fichier);
}

void testRadius()
{
	PGMValeurs *fichier = NULL;
	int ***rondelles = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/2/radius_";

		if (i == 9)
		{
			test(chemin_fich, i, rondelles, 0);
		}
		else
		{
			test(chemin_fich, i, rondelles, 1);
		}

		free(rondelles);

		printf("\n");
	}

	free(fichier);
}

void testDefect()
{
	PGMValeurs *fichier = NULL;
	int ***rondelles = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/3/defect_";

		test(chemin_fich, i, rondelles, 1);

		free(rondelles);

		printf("\n");
	}

	free(fichier);
}

void testMultiple()
{
	PGMValeurs *fichier = NULL;
	int ***rondelles = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/4/multiple_";

		test(chemin_fich, i, rondelles, 0);

		free(rondelles);

		printf("\n");
	}

	free(fichier);
}

void testMultipleRadius()
{
	PGMValeurs *fichier = NULL;
	int ***rondelles = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/5/multiple_radius_";

		test(chemin_fich, i, rondelles, 1);

		free(rondelles);

		printf("\n");
	}

	free(fichier);
}

void testMultipleDefect()
{
	PGMValeurs *fichier = NULL;
	int ***rondelles = NULL;

	for (int i = 0; i < 10; i++)
	{
		char chemin_fich[MAX] = "dataset/6/multiple_defect_";

		test(chemin_fich, i, rondelles, 1);

		free(rondelles);

		printf("\n");
	}

	free(fichier);
}

int main(int argc, char const *argv[])
{
	testsSingle();
	testRadius();
	testDefect();
	testMultipleRadius();
	testMultipleDefect();

	// Les deux derniers tests ne marchent pas car les rondelles sont trop proches.
	testMultiple();

	return 0;
}