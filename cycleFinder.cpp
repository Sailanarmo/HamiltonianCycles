#include <vector>
#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <cstdlib>
#include <unordered_set>

#define DEBUG 0
//define std::hash for an unordered set
namespace std {
  template <>
  struct hash<std::unordered_set<int> >
  {
    int operator()(const std::unordered_set<int> & s) const
    {
			int setHash=0;
			for(auto &&e: s)
			{
				setHash+=pow(2,e); //check if this is implemeted with bitshift when powers of two, (likely isnt)
			}
				
      return setHash;
    }
  };
}


void printCycle(std::unordered_set<int> cycle)
{
		std::cout << "{ ";
		for(auto &&v: cycle)
		{
			std::cout << v << " ";
		}
		std::cout << "}";
}

void printHashes(std::unordered_set<std::unordered_set<int> > cycleList)
{
	for(auto &&c: cycleList)
	{
		//XOR the hashes of c and cycle
		//Check if a power of two. If yes, is a cycle that extends
		int hashSum = 0;
		std::cout << "{ ";
		for(auto &&v: c)
		{
			std::cout << v << " ";
			hashSum += pow(2,v);
		}
		std::cout << "} hashes to " << hashSum << std::endl;
	}
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
	if(vy == initialy && path.size() <= 2 && path.size()>0)
	{ 
#if DEBUG
		std::cout << "2-path" << std::endl; 
#endif
		return;
		}// 2-cycles are not acceptable

	if(vy == initialy && path.size() > 2)
	{
		path.push_back(vy); //add current vertex to our path through the graph
		cycleList.insert(std::unordered_set<int>(path.begin(),path.end())); //found a cycle, add it to the set of sets
#if DEBUG
		std::cout << "pushed cycle" << std::endl;
#endif
		return; // Cycles can not continue through a visited vertex
	}

	path.push_back(vy); //add current vertex to our path through the graph

	//Go to each ajdacent vertex, as long as it is not visited in our path already
	for(int i=0; i<G[vy].size(); ++i)
	{
		if(visited[i] != true && G[vy][i] == 1)
		{
			#if DEBUG
			std::cout << "Going from " << vy << " to " << i << std::endl;
			#endif
			buildCycleList(G,visited,cycleList,i,initialy,path); //move to row of the next vertex and keep searching recursively
		}
	}
	#if DEBUG
	std::cout << "exhausted adjacencies on " << vy << std::endl;
	#endif

}

bool cycleExtends(std::unordered_set<int> cycle, std::unordered_set<std::unordered_set<int> > cycleList)
{
	//fancy bit level XOR AND here
	
	int origCycleHash = 0;
	
	for(auto &&v: cycle)
	{
		origCycleHash += pow(2,v);
	}

	for(auto &&c: cycleList)
	{
		//XOR the hashes of c and cycle
		//Check if a power of two. If yes, is a cycle that extends
		int hashSum = 0;
		for(auto &&v: c)
		{
			hashSum += pow(2,v);
		}

		int bitXOR = origCycleHash ^ hashSum; // if results in power of two, good
		int bitAND = origCycleHash & hashSum;
		int pow2check = bitXOR & (bitXOR)-1;
#if DEBUG
		std::cout << "origCycleHash: " << origCycleHash << std::endl;
		std::cout << "hashSum: " << hashSum << std::endl;
		std::cout << "bitAND: " << bitAND << std::endl;
		std::cout << "bitXOR: " << bitXOR << std::endl;
		std::cout << "2-power check: " << pow2check << std::endl << std::endl;
#endif

		//a power of two will only have a single bit set, and so 1 less than that will have all lesser bits set to 1
		//then if you AND it with the original, all bits should be different
		//
		//if the original cycle AND the possibly extending cycle result in the original cycle, it must have contain all the vertices of the original.
		
		if(bitAND == origCycleHash && cycle != c)
		{
			//if(bitXOR & (bitXOR-1) == 0 && origCycleHash & hashSum == origCycleHash) 
			if(pow2check == 0 ) 
			{
				printCycle(c);
				std::cout << " extends ";
				printCycle(cycle);
				std::cout << std::endl;
				return true;
			}
		}
	}

	return false;
}

bool graphExtends(std::unordered_set<std::unordered_set<int> > cycleList, int vertices)
{
	for(auto &&c: cycleList)
	{
		if(c.size() < vertices && !cycleExtends(c,cycleList)) //dont check hamiltonian cycles (TODO:optimize for n < v-1 and n > 4)
			return false; //found a cycle that does not extend, thus graph does not extend
	}
	return true; //All cycles extend
}


void runOnFile(int vertices, std::string file)
{
	std::vector<std::vector<bool> > G;
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
			int temp;
			fin >> temp;   // read in as int and cast to bool, as std::cin does not support reading boolean from file
			c = (bool)temp;
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

	if(graphExtends(cycleList,vertices)) std::cout << "G extends" << std::endl;
	else 
	{
		std::cout << "G does not extend" << std::endl;
		printAdj(G);
	}
}

int main(int argc, char* argv[])
{
	int vertices = 0;
	std::string file;

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

	runOnFile(vertices,file);

}
