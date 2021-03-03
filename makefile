OBJS = histogramme.o
OUT = histogramme

SOURCE = histogramme.c
HEADER = pgm.h

FLAGS = -Wall
CC = gcc

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

$(OBJS): $(SOURCE)
	$(CC) $(FLAGS) -c $(SOURCE)

fichierRondelle: fichierRondelle.c
	$(CC) $(FLAGS) -o fichierRondelle fichierRondelle.c pgm.h

clean:
	rm -f $(OBJS) $(OUT)