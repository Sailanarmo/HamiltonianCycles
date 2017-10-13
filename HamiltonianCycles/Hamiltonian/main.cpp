/*
 * C++ Program to Find Hamiltonian Cycle
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>

#define V 12


void printSolution(int path[]);

/* 
 * check if the vertex v can be added at index 'pos' in the Hamiltonian Cycle 
 */
bool isSafe(int v, bool graph[V][V], int path[], int pos)
{
	if (graph [path[pos-1]][v] == 0)
		return false;
	for (int i = 0; i < pos; i++)
		if (path[i] == v)
			return false;
	return true;
}

/* solve hamiltonian cycle problem */
bool hamCycleUtil(bool graph[V][V], int path[], int pos)
{
	if (pos == V)
	{
		if (graph[ path[pos-1] ][ path[0] ] == 1)
			return true;
		else
			return false;
	}

	for (int v = 1; v < V; v++)
	{
		if (isSafe(v, graph, path, pos))
		{
			path[pos] = v;
			if (hamCycleUtil (graph, path, pos+1) == true)
				return true;
			path[pos] = -1;
		}
	}
	return false;
}

/* solves the Hamiltonian Cycle problem using Backtracking.*/
bool hamCycle(bool graph[V][V])
{
	int *path = new int[V];
	for (int i = 0; i < V; i++)
		path[i] = -1;
	path[0] = 0;
	if (hamCycleUtil(graph, path, 1) == false)
	{
		//std::cout<<"\nSolution does not exist"<< std::endl;
		return false;
	}
	//printSolution(path);


	return true;
}

/* Main */
/*
	 void printSolution(int path[])
	 {
	 std::cout<<"Solution Exists:";
	 std::cout<<" Following is one Hamiltonian Cycle \n"<< std::endl;
	 for (int i = 0; i < V; i++)
	 std::cout<<path[i]<<"  ";
	 std::cout<< path[0]<<std::endl;
	 }
	 */
int main ( int argc, char *argv[] )
{
	if (argc != 4)
	{
		std::cout << "ham <vertex count> <input file> <output file>" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "verts:  " << argv[2] << std::endl;
	std::cout << "input:  " << argv[2] << std::endl;
	std::cout << "output: " << argv[3] << std::endl;

	std::string infile(argv[2]);
	std::string outfile(argv[3]);
	std::ofstream output(infile);
	std::string row;
	int poopmatrix[V][V];
	bool realmatrix[V][V];

	std::chrono::duration<double> time;

	auto start = std::chrono::high_resolution_clock::now();

	while(std::getline(std::cin, row))
	{
		std::getline(std::cin, row);
		for(int i = 0; i < V; ++i)
		{
			std::getline(std::cin, row);
			//std::cout << row << "     ";
			for(int j = 0; j < V; ++j)
			{
				if(row[0] != 0 || row[0] != 1) std::cerr << "Oh no!\n\n";
				poopmatrix[i][j] =(int)row[j] - 48;
				realmatrix[i][j] = (bool)poopmatrix[i][j];
				//std::cout << realmatrix[i][j] << " ";
			}
			//std::cout << std::endl;
		}
		//std::cout << std::endl;

		if(hamCycle(realmatrix) == true)
		{
			for(int i = 0; i < V; ++i)
			{
				for (int j =0; j < V; ++j)
				{
					output << realmatrix[i][j] << " " ;
				}
				output << "\n";
			}
			output << "\n";
		}

	}

	auto end = std::chrono::high_resolution_clock::now();

	time = end - start;

	std::cout << "Computation took: " << time.count() << " Seconds." << std::endl;
	return EXIT_SUCCESS;
}
