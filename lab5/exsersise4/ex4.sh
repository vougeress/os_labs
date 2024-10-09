#!/bin/bash

gcc ex4.c -o ex4 -lpthread
result_file="ex4_res.txt"
echo "" > $result_file

for m in 1 2 4 10 100; do
    start_time=$(date +%s.%N)
    ./ex4 10000000 $m
    end_time=$(date +%s.%N)
    elapsed=$(echo "$end_time - $start_time" | bc)
    echo "m = $m: $elapsed seconds" >> $result_file
done
