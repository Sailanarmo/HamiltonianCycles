#!/usr/bin/env bash

for i in {0..8}; do
  echo starting $i
  .././listg -a ../../../../Graphs/FilteredWithoutHamiltonian/split12/filteredHamiltonainOn120$i.g6 | ../../../HamiltonianCycles/Hamiltonian/./a.out out0$i.adj &
  sleep .25
done
