#!/usr/bin/env bash

if (( $# != 2)); then
	echo "requires 2 input files, output goes to std out"
	echo "<larger file> <smaller file>"
else
	diff --side-by-side --suppress-common-lines $1 $2 | sed 's/<//g' | sed 's/[[:space:]]*$//'
fi

exit
