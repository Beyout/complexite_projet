#include <stdio.h>
#include <stdlib.h>
#include "structFichier.h"

/**********************File I/O functions*******************************/
/***********************************************************************/

/*Gets an ascii pgm image file, store as a color pgm.*/
PGMValeurs getPGMfile(char *chemin, PGMValeurs *fichier)
{
	FILE *in_file;
	char ch;
	int type;

	in_file = ouvreFichier(chemin);
	int ligne = getc(in_file);


	// Entête du fichier
	for (int i = 0; i < 3; i++)
	{
		getc(in_file);
	}
	


	int i = 0;
	int j = 0;

	while (ligne != -1)
	{ /* skip to end of line*/
		if ((char)ligne == '\n' || i == 512)
		{
			j++;
			i = 0;
		}
		else
		{
			if (ligne < 50)
			{
				// Noir : 0
				fichier->valeurs[i][j] = 0;
			}
			else
			{
				// Blanc : 255
				fichier->valeurs[i][j] = 255;
			}

			i++;
		}
		ligne = getc(in_file);
	}

	fclose(in_file);
	printf("\nDone reading file.\n");

	return *fichier;
}

/**
 * Ouvre le fichier dont le chemin est passé en paramètre, affiche les erreurs et terminent le programme s'il y en a.
 */
FILE* ouvreFichier(char* chemin) {
	char ch;
	int type;

	FILE* in_file = fopen(chemin, "r");
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

int main(void)
{
	PGMValeurs *fichier = malloc(sizeof(PGMValeurs));
	getPGMfile("dataset/1/single_0.pgm", fichier);
	
	free(fichier);
	return 0;
}
