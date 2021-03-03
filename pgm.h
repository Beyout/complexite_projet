#include <stdio.h>
#include <stdlib.h>
#include "structFichier.h"

/**
 * Ouvre le fichier dont le chemin est passé en paramètre, affiche les erreurs et terminent le programme s'il y en a.
 */
FILE *ouvreFichier(char *chemin)
{
	char ch;
	int type;

	FILE *in_file = fopen(chemin, "r");
	if (in_file == NULL)
	{
		fprintf(stderr, "Error: Unable to open file %s\n\n", chemin);
		exit(8);
	}

	printf("\nReading image file: %s\n", chemin);

	/*determine pgm image type (only type three can be used)*/
	ch = getc(in_file);
	if (ch != 'P')
	{
		printf("ERROR(1): Not valid pgm/ppm file type\n");
		exit(1);
	}
	ch = getc(in_file);
	/*convert the one digit integer currently represented as a character to
		an integer(48 == '0')*/
	type = ch - 48;
	if ((type != 2) && (type != 3) && (type != 5) && (type != 6))
	{
		printf("ERROR(2): Not valid pgm/ppm file type\n");
		exit(1);
	}

	return in_file;
}

/** Récupére les valeurs des pixels et les met dans la structure fichier passée en paramètre dont on spécifie le chemin */
void getPGMfile(char *chemin, PGMValeurs *fichier)
{
	FILE *in_file;

	in_file = ouvreFichier(chemin);
	int ligne = getc(in_file);

	// Entête du fichier
	int nbN = 0;
	while (nbN < 3)
	{
		if (ligne == 10)
		{
			nbN++;
		}
		ligne = getc(in_file);
	}

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			fichier->valeurs[i][j] = ligne;
			ligne = getc(in_file);
		}
	}

	fclose(in_file);
	printf("\nDone reading file.\n");
}