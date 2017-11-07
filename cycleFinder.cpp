#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <unordered_set>

namespace std {
  template <>
  struct hash<std::unordered_set<int> >
  {
    //typedef Set      argument_type;

    int operator()(const std::unordered_set<int> & s) const
    {
			int setHash=0;
			for(auto &&e: s)
			{
				setHash+=pow(2,e); //check if this is implemeted with bitshift when powers of two, (likely is)
			}
				
      return setHash;
    }
  };
}


void printAdj(std::vector<std::vector<bool> > G) 
{
	for(auto &&r : G)
	{
		for(auto &&c : r)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

//we use only the rows, and almost treat each row as an adjacency list, using the index of the vertex as the index
void buildCycleList(std::vector<std::vector<bool> > G, std::vector<bool> visited, std::unordered_set<std::unordered_set<int> > &cycleList, int vy, int initialy, std::vector<int> path)
{
	visited[vy] = true;
	visited[initialy] = false;
	if(vy == initialy && path.size() <= 2 && path.size()>0){ std::cout << "2-path" << std::endl; return;}// 2-cycles are not acceptable
	if(vy == initialy && path.size() > 2)
	{
		path.push_back(vy); //add current vertex to our path through the graph
		cycleList.insert(std::unordered_set<int>(path.begin(),path.end())); //found a cycle, add it to the set of sets
		std::cout << "pushed cycle" << std::endl;
		return; // Cycles can not continue through a visited vertex
	}

	path.push_back(vy); //add current vertex to our path through the graph

	//Go to each ajdacent vertex, as long as it is not visited in our path already
	for(int i=0; i<G[vy].size(); ++i)
	{
		if(visited[i] != true && G[vy][i] == 1)
		{
			std::cout << "Going from " << vy << " to " << i << std::endl;
			buildCycleList(G,visited,cycleList,i,initialy,path); //move to row of the next vertex and keep searching recursively
		}
	}
	std::cout << "exhausted adjacencies on " << vy << std::endl;

}

int main(int argc, char* argv[])
{
	int vertices = 0;
	std::string file;
	std::vector<std::vector<bool> > G;

	//get arguments
	if(argc != 3)
	{	
		std::cout << "Enter the number of vertices: ";
		std::cin >> vertices;
		std::cout << "Enter graph file: ";
		std::cin >> file;
	}
	else
	{
		vertices = atoi(argv[1]);
		file = argv[2];
	}

	//initialize parameters
	G.resize(vertices);
	for(auto &&v : G)
	{
		v.resize(vertices);
	}

	std::ifstream fin;
	fin.open(file);
	
	for(auto &&r : G)
	{
		for(auto &&c : r)
		{
			int rekt;
			fin >> rekt;
			c = (bool)rekt;
		}
	}

	printAdj(G);

	std::vector<bool> visited(vertices,0);
	std::unordered_set<std::unordered_set<int> > cycleList;
	std::vector<int> path;
	for(int i=0; i< vertices; ++i)
	{
		buildCycleList(G,visited,cycleList,i,i,path);
	}

	//print cycles
  //std::unordered_set<std::unordered_set<int> > newList(cycleList.begin(),cycleList.end());
	for(auto &&l: cycleList)
	{
		for(auto &&e: l)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	printAdj(G);

	std::cout << vertices << std::endl;


}
