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

#define V 2


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

/* solve Hamiltonian cycle problem */
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
    delete [] path;
    return false;
  }
  //printSolution(path);

  delete [] path;
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
int main(int argc, char* argv[])
{

  if(argc != 2)
  {
    std::cout << "ham.out <output file>" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << argv[1] << std::endl;

  std::ofstream output(argv[1]);
  std::string vert;
  bool m[V][V];
  unsigned int hamGraphs = 0u;

  std::cout << "Starting: " << argv[1] << " on " << V << " vertices" << std::endl;

  std::chrono::duration<double> time;

  auto start = std::chrono::high_resolution_clock::now();

  while(std::getline(std::cin, vert))
  {
    std::getline(std::cin,vert);
    for(int i=0; i< V; ++i)
    {
      std::getline(std::cin, vert);
      //std::cout << vert << "     ";
      for(int j=0;j<V; ++j)
      {
        //if(vert[0] != 0 || vert[0] != 1) std::cerr;
        m[i][j] = (bool)(vert[j]- 48);
        //std::cout << realmatrix[i][j] << " ";
      }
      //std::cout << std::endl;
    }
    //std::cout << std::endl;

    if(hamCycle(m) == true)
    {
      ++hamGraphs;
      for(int i = 0; i < V; ++i)
      {
        for (int j =0; j < V; ++j)
        {
          output << m[i][j] << ' ' ;
          //std::cout << realmatrix[i][j] << " " ;
        }
        output << '\n';
        //std::cout << "\n";
      }
      output << '\n';
      //std::cout << std::endl;
    }
  }

  output.close();

  auto end = std::chrono::high_resolution_clock::now();

  time = end - start;

  std::cout << "Finished:\t\t" << argv[1] << '\n';
  std::cout << "Computation took:\t" << time.count() << " Seconds.\n";
  std::cout << "Hamiltonian Graphs:\t" << hamGraphs << std::endl;

  return 0;
}
