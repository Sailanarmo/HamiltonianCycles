#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

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
void buildCycleList(std::vector<std::vector<bool> > G, std::vector<bool> visited, std::vector<std::vector<int> > &cycleList, int vy, int initialy, std::vector<int> path)
{
	visited[vy] = true;
	visited[initialy] = false;
	if(vy == initialy && path.size() <= 2 && path.size()>0){ std::cout << "2-path" << std::endl; return;}// 2-cycles are not acceptable
	if(vy == initialy && path.size() > 2)
	{
		path.push_back(vy); //add current vertex to our path through the graph
		cycleList.push_back(path); //found a cycle, push it back
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
			buildCycleList(G,visited,cycleList,i,initialy,path); //move to row of the next vertex and keep searching
		}
	}
	std::cout << "exhausted adjacencies on " << vy << std::endl;

}

int main(int argc, char* argv[])
{
	int vertices = 0;
	std::string file;
	std::vector<std::vector<bool> > G;

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


	std::vector<bool> visited(vertices,0);
	std::vector<std::vector<int> > cycleList;
	std::vector<int> path;
	buildCycleList(G,visited,cycleList,0,0,path);


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
