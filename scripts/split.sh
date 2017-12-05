#!/usr/bin/env bash

if (( $# != 3)); then
  echo "requires 3 arguments"
  echo "<file> <number of lines per file> <file prefix>"
else
  split -l $2 -d --additional-suffix=.g6 $1 $3
fi

exit
