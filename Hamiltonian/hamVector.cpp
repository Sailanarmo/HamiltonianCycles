#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>

void printSolution(int path[]);

/* 
 * Check if the vertex v can be added at index 'pos' in the Hamiltonian Cycle 
 */
bool isSafe(int v, const std::vector<std::vector<bool>>& graph, const std::vector<int> path, int pos)
{
  if (graph [path[pos-1]][v] == 0)
    return false;
  for (int i = 0; i < pos; ++i)
    if (path[i] == v)
      return false;
  return true;
}

/*
 * Solve Hamiltonian Cycle Problem
 */
bool hamCycleUtil(const std::vector<std::vector<bool>>& graph, std::vector<int> path, int pos, int V)
{
  if (pos == V)
  {
    if (graph[ path[pos-1] ][ path[0] ] == 1)
      return true;
    else
      return false;
  }

  for (int v = 1; v < V; ++v)
  {
    if (isSafe(v, graph, path, pos))
    {
      path[pos] = v;
      if (hamCycleUtil (graph, path, pos+1, V) == true)
        return true;
      path[pos] = -1;
    }
  }
  return false;
}

/*
 * Solve the Hamiltonian Cycle problem using Backtracking.
 */
bool hamCycle(const std::vector<std::vector<bool>>& graph, int V)
{
  std::vector<int> path(V,-1);
  path[0] = 0;
  if (hamCycleUtil(graph, path, 1, V) == false)
  {
    //std::cout<<"\nSolution does not exist"<< std::endl;
    return false;
  }
  //printSolution(path);

  return true;
}

int main(int argc, char* argv[])
{

  if(argc != 3)
  {
    std::cout << "ham.out <vertex number> <output file>" << std::endl;
    return EXIT_FAILURE;
  }

  std::ofstream output(argv[2]);
  const int V(std::stoi(argv[1]));
  std::string row, trash;
  unsigned int hamGraphs = 0u;
  std::chrono::duration<double> time;

  std::cout << "Starting: " << argv[2] << " on " << V << " vertices" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();

  std::vector<std::vector<bool>>m(V, std::vector <bool>(V,0));
  while(std::getline(std::cin, trash))
  {
    std::getline(std::cin, trash);
    for(int i = 0; i < V; ++i)
    {
      std::getline(std::cin, row);
      for(unsigned j = 0u; j < row.size(); ++j)
      {
        m[i][j]=(row[j] - 48);
        //std::cout << m[i][j] << " ";
      }
      //std::cout << std::endl;
    }
    //std::cout << std::endl;

    if(hamCycle(m, V) == true)
    {
      ++hamGraphs;
      for(int i = 0; i < V; ++i)
      {
        for (int j =0; j < V; ++j)
        {
          output << m[i][j] << ' ' ;
        }
        output << '\n';
      }
      output << '\n';
    }
  }

  output.close();

  auto end = std::chrono::high_resolution_clock::now();

  time = end - start;

  std::cout << "\nFinished:\t\t" << argv[2] << '\n';
  std::cout << "Computation took:\t" << time.count() << " Seconds.\n";
  std::cout << "Hamiltonian Graphs:\t" << hamGraphs << std::endl;

  return EXIT_SUCCESS;
}
