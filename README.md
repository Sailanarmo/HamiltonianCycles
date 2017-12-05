<img src="/resources/Mathematics-Logo_BLUE.png">

## Hamiltonian and Non-Extending Chordal Graphs

This repository is for a research group under the direction of <a href="http://www.math.usu.edu/people/davidbrown_facultypage.php">Dr. David Brown</a> and <a href="http://www.math.usu.edu/people/brent-thomas.php">Brent Thomas</a> at Utah State University. Our goal is to help ourselves and others analyze graphs for hamiltonicity and cycle extend-ability. We are using Dr. Brendan McKay's Nauty Software and Algorithms. All credit of the `nauty26r7` directory belongs solely to the work of Dr. Brendan McKay who's software can be found here: <a href="http://pallini.di.uniroma1.it/">nauty and Traces</a>.

#### Hamiltonian Cycles and Hamiltonicity
`Hamiltonian/` contains resources for checking hamiltonicity in graphs. `ham.cpp` is used like:

```
listg -a <source file.g6> | ham.out <source file.g6> <output file.g6>
```

#### Cycles and Cycle Extend-ability

`Extendable/` contains resources for checking cycle extend-ability in graphs. `cycleFinder.cpp` contains helper functions for `notExtendable` and `singleThread`.

`cycles.cpp` is a program that will take an input file formatted as space separated adjacency matrices, where each adjacency matrix is set off from the others with a new line. The program will ask for the number of vertices and the file to read from. It can also be given these input parameters as command line arguments. The program cycles.out is used like:

```
./cycles.out <verticies> <output file.adj>
```

`notExtendable.cpp` is a multi threaded program that reads adjacency matrices produced from `listg -Aq` and writes the graphs that are **not** cycle extendable to a file. It will determine the number of concurrent threads supported by the system and search all the graphs fed to if from listg. The chunk size is the number of graphs that each thread will process at a time. The program notExtendable is used like:

```
listg -Aq <file.g6> | ./notExtendable.out <vertices> <chunk size>
```
