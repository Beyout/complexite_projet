OBJS = analyser.o
OBJS_REPORT = analyser_report.o
OBJS_SAVE = analyser_save.o
OBJS_TEST = test.o

OUT = analyser
OUT_REPORT = analyser_report
OUT_SAVE = analyser_save
OUT_TEST = test

SOURCE = analyser.c
TEST = test.c
HEADER = pgm.h histogramme.h fichierRondelle.h structFichier.h traitementRondelle.h
REPORT = -DREPORT
SAVE = -DSAVE

FLAGS = -Wall -lm
CC = gcc

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(FLAGS) 

$(OUT_REPORT): $(OBJS_REPORT)
	$(CC) $(OBJS) -o $(OUT_REPORT) $(FLAGS) 

$(OUT_SAVE): $(OBJS_SAVE)
	$(CC) $(OBJS) -o $(OUT_SAVE) $(FLAGS)

$(OUT_TEST): $(OBJS_TEST)
	$(CC) $(OBJS) -o $(OUT_TEST) $(FLAGS)


$(OBJS): $(SOURCE)
	$(CC) -c $(SOURCE) 

$(OBJS_REPORT): $(SOURCE)
	$(CC) -c $(SOURCE) $(REPORT)
	
$(OBJS_SAVE): $(SOURCE)
	$(CC) -c $(SOURCE) $(REPORT) $(SAVE)

$(OBJS_TEST): $(TEST)
	$(CC) -c $(TEST)


clean:
	rm -f $(OUT) $(OUT_REPORT) $(OUT_SAVE) $(OUT_TEST) $(OBJS) $(OBJS_REPORT) $(OBJS_SAVE) $(OBJS_TEST)