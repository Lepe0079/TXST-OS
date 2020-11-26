#!/bin/bash
g++ main.cpp -w -o sim -std=c++11
for ((i = 1; i <=30; i++)); do 
    ./sim 1 $i 0.06 0.01
    cp sim.data data/sim-1-$i-001.data
    rm sim.data
done
