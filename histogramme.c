#include "pgm.h"

void dessineHistogramme (char* chemin) {
	PGMValeurs *fichier = malloc(sizeof(PGMValeurs));
	getPGMfile(chemin, fichier);

	int tab[32];

	for (int i = 0; i < 32; i++)
	{
		tab[i] = 0;
	}
	

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			
		}
		
	}
	

	free(fichier);
	return 0;
}

int main(int argc, char const *argv[])
{
	dessineHistogramme("dataset/1/single_0.pgm");
	return 0;
}
