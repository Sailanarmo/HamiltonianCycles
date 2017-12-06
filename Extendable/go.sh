#!/usr/bin/env bash

if [ "$#" -ne 3 ]; then
  echo "go.sh <input file.g6> <vertices> <chunk size>"
  exit
fi

listg -Aq $1 | ./notExtendable.out $2 $3
cat out* > notExtendableOn$2.adj
rm out*

exit
