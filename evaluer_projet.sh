#!/bin/bash
make clean
make
max=9
for i in `seq 0 $max`
do
    for file in dataset/4/multiple_$i.pgm
    do
        ./analyser $file >>resultats.csv
    done
done
