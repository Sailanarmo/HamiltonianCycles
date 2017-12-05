#!/usr/bin/env bash

if [ "$#" -ne 2 ]; then
  echo "go.sh <vertices> <input file prefix>#.g6"
  exit
fi

cd ~/Documents/HamiltonianCycles/HamiltonianCycles/Hamiltonian
sed -i "s/\(#define\sV\s\)[0-9]\+/\1$1/" ham.cpp
make
cd -


for i in {0..7}; do
  echo "starting $2$i.g6"
  listg -a $2$i.g6 | ham $2$i.g6 out0$i.adj &
  sleep .25
done
