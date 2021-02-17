#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pgm.h"
 
/**********************File I/O functions*******************************/
/***********************************************************************/
 
/*Gets an ascii pgm image file, store as a color pgm.*/
void getPGMfile (char filename[], PGMImage *img)
{
   FILE *in_file;
   char ch;
   int type;
  
   in_file = fopen(filename, "r");
   if (in_file == NULL)
   {
     fprintf(stderr, "Error: Unable to open file %s\n\n", filename);
     exit(8);
   }
  
   printf("\nReading image file: %s\n", filename);
    
   /*determine pgm image type (only type three can be used)*/
   ch = getc(in_file);
   if(ch != 'P')
   {
     printf("ERROR(1): Not valid pgm/ppm file type\n");
     exit(1);
     getc(in_file);
   }
   ch = getc(in_file);
   /*convert the one digit integer currently represented as a character to
    an integer(48 == '0')*/
   type = ch - 48;
   if((type != 2) && (type != 3) && (type != 5) && (type != 6))
   {
      printf("ERROR(2): Not valid pgm/ppm file type\n");
      exit(1);
   }
    int ligne  = getc(in_file);
    int nbN = 0;
    while(nbN<3){
	if(ligne==10){
		nbN++;
	}
	ligne  = getc(in_file);
    }

    //ligne  = getc(in_file);
    int temps =0;
    int longueur =0;
    int i=0;
    int j=0;
    while(!feof( in_file )){
	if(longueur==512){
		printf("\n");
		printf("longueur -> %d\n", longueur);
		longueur=0;
		i++;
		j=0;
	}
	else{	
		if(ligne<60){
			printf("x");
			printf("ici\n");
			img->data[i][j] = 0;
		}
		else{
			printf("o");
			printf("la %d et %d\n", i, j);
			img->data[i][j] = 255;
		}
		j++;
		longueur++;
	}
	//printf("%d", ligne);
	//printf("\n");
	//sleep(1);
	printf(" ");

	ligne  = getc(in_file);
    }
  
    fclose(in_file);
    printf("\nDone reading file.\n");
  }

void save(PGMImage *img)
{
     int i, j, nr, nc, k;
     int red, green, blue;
     FILE *iop;
  
     nr = 512;
     nc = 512;
      
     iop = fopen("image1.pgm", "w");
     fprintf(iop, "P6\n");
     fprintf(iop, "%d %d\n", nc, nr);
     fprintf(iop, "255\n");
     printf("ici");
     k = 1;
     for(i = 512; i  > -1; i--)
     {
        for(j = 512; j >  -1; j--)
        {
           int gris = img->data[i][j];
  	   putc(gris, iop);
	   printf("tab[%d][%d] -> %d\n", i, j, gris);
	   //getchar();
        }
     }     fprintf(iop, "\n");
     fclose(iop);
}


int main(void){
	PGMImage *img = malloc(sizeof(PGMImage));
	getPGMfile ("radius_4.pgm", img);
	printf("ici");
	save(img);
	free(img);
	return 0;
}

