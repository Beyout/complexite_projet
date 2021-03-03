#include<stdio.h>
#include "pgm.h"

void construitFichierRondelle(char *chemin)
{
	PGMValeurs *fichier = malloc(sizeof(PGMValeurs));
	getPGMfile(chemin, fichier);

	for (int i = 0; i < 512; i++)
	{
		printf("LIGNE %d\n", i);
		for (int j = 0; j < 512; j++)
		{
			printf("%4d", fichier->valeurs[i][j]);
		}
		printf("\n");
	}
	

	int xmin = 512;
	int ymin = 512;
	int xmax = 0;
	int ymax = 0;

	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			if(fichier->valeurs[y][x] == 0) {
				if(x < xmin) {
					xmin = x;
				}
				else if(x > xmax) {
					xmax = x;
				}
				
				if(y < ymin) {
					printf("%d %d | %d\n", x, y, fichier->valeurs[y][x]);
					ymin = y;
				}
				else if(y > ymax) {
					ymax = y;
				}
			}
		}
		
	}
	
	printf("%d %d %d %d\n", xmin, xmax, ymin, ymax);

	FILE* destination;
	destination = fopen("rondelle.pgm", "w");
	fprintf(destination, "P5\n");
	fprintf(destination, "%d %d\n", xmax - xmin, ymax - ymin);
	fprintf(destination, "255\n");

	for (int y = ymin; y < ymax; y++)
	{
		for (int x = xmin; x < xmax; x++)
		{
			int px = fichier->valeurs[y][x];
			putc(px, destination);
		}
	}
	fprintf(destination, "\n");
	fclose(destination);
}

int main(int argc, char const *argv[])
{
	construitFichierRondelle("dataset/1/single_0.pgm");
	return 0;
}
