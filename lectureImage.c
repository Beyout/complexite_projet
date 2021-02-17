#include <stdio.h>
#include <stdlib.h>

char* lireImage(char* chemin) {
	FILE *input;
	char* buff;

	input = fopen(chemin, "r");

	long longueurFichier = ftell(input);

	buff = (char *) malloc(longueurFichier);

	fscanf(input, "%s", buff);
	fclose(input);
}

int main(int argc, char const *argv[])
{
	lireImage("dataset/1/single_0.pgm");
	return 0;
}
