#!/bin/bash

N=$1

mkdir -p /tmp/ex1
gnome-terminal -- bash -c "./publisher $N; exec bash"
for ((i = 1; i <= N; i++)); do
    gnome-terminal -- bash -c "./subscriber $i; exec bash"
done
echo " " > ex1.txt

echo "Publisher and $N subscribers have been started in separate terminal windows."
