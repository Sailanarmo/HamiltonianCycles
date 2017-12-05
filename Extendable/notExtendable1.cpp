#include "threadSafeQueue.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using Graph = std::vector<std::vector<bool>>;

void feedQueue(TSQ<std::vector<Graph>>& queue, int vertices, int chunkSize)
{
  Graph g;
  g.resize(vertices);
  for (auto&& r : g) r.resize(vertices);

  int tmp;
  int trash;
  for (;;)
  {
    std::vector<Graph> graphs;
    for (int i = 0; i < chunkSize; ++i)
    {
      if ((std::cin.eof()))
      {
        std::cout << '\n' << "END OF STDIN" << std::endl;
        if (graphs.size() != 0) queue.enqueue(graphs);
        queue.done();
        return;
      }
      std::cin >> trash;

      for (auto&& r : g)
      {
        for (auto&& c : r)
        {
          std::cin >> tmp; // read in as int and cast to bool, std::cin does not support
                           // reading Boolean from file
          c = (bool)tmp;
        }
      }
      graphs.push_back(g);
    }
    queue.enqueue(graphs);
  }
}

int main(int argc, char* argv[])
{
  int vertices = 0;

  // get arguments
  if (argc != 2)
  {
    std::cout << "<vertices> /* get input from listg -Aq */" << std::endl;
    return EXIT_FAILURE;
  }
  vertices = atoi(argv[1]);

  TSQ<std::vector<Graph>> queue;

  std::thread feeder([&]() { feedQueue(queue, vertices, 5); });

  feeder.join();

  std::cout << queue.size() << " chunks on queue :D " << std::endl;
}
