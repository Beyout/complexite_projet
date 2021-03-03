#include<stdio.h>
#include "pgm.h"

void construitFichierRondelle(char *chemin)
{
	PGMValeurs *fichier = malloc(sizeof(PGMValeurs));
	getPGMfile(chemin, fichier);	

	int xmin = 512;
	int ymin = 512;
	int xmax = 0;
	int ymax = 0;

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			if(fichier->valeurs[i][j] < 48) {
				if(j < xmin) {
					xmin = j;
				}
				else if(j > xmax) {
					xmax = j;
				}
				
				if(i < ymin) {
					printf("x: %d y: %d\n", j, i);
					ymin = i;
				}
				else if(i > ymax) {
					ymax = i;
				}
			}
		}
		
	}
	printf("%d\n", fichier->valeurs[327][326]);
	printf("%d %d %d %d\n", xmin, xmax, ymin, ymax);

	FILE* destination;
	destination = fopen("rondelle.pgm", "w");
	fprintf(destination, "P5\n");
	fprintf(destination, "%d %d\n", (xmax - xmin) + 1, (ymax - ymin) + 1);
	fprintf(destination, "255\n");

	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
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
	construitFichierRondelle("dataset/3/defect_0.pgm");
	return 0;
}
