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

rayon: rayon.c
	$(CC) $(FLAGS) -o rayon rayon.c

clean:
	rm -f $(OBJS) $(OUT)