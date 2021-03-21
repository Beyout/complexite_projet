OBJS = rayon.o
OUT = rayon

SOURCE = rayon.c
HEADER = pgm.h histogramme.h fichierRondelle.h structFichier.h

FLAGS = -Wall
MATH = -lm
CC = gcc

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(MATH)

$(OBJS): $(SOURCE)
	$(CC) $(FLAGS) -c $(SOURCE)


clean:
	rm -f $(OBJS) $(OUT)