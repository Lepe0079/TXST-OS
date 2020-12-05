#!/bin/bash
make
mkdir -p data
for ((x = 0; x < 3; ++x))
do
    for ((i = 1; i <=30; i++)); 
    do 
        ./pageSim $x $i 30
    done
    cp pagefault.csv data/pgFault-$x.csv
    rm pagefault.csv
done
rm *.o
