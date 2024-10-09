#!/bin/bash

gcc ex3.c -o ex3 -lpthread
result_file="ex3_res.txt"
echo "" > $result_file
for m in 1 2 4 10 100; do
    start_time=$(date +%s.%N)
    ./ex3 10000000 $m
    end_time=$(date +%s.%N)
    elapsed=$(echo "$end_time - $start_time" | bc)
    echo "m = $m: $elapsed seconds" >> $result_file
done