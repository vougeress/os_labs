#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <message>"
    exit 1
fi

for i in {1..10}
do
    echo "Run $i:"
    ./ex1 "$1"
done
