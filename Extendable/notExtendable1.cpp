#include "cycleFinder.cpp"
#include "threadSafeQueue.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
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
    //std::cout << "POST" << std::endl;
  }
}

void processQueue(TSQ<std::vector<Graph>>& queue, int vertices, std::ofstream& fout)
{
  std::vector<Graph> graphs;
  for (;;)
  {
    if (queue.dequeue(graphs))
    {
      //std::cout << "processing" << std::endl;
      process(vertices, graphs, fout);
    }
    else if (!queue.hasMore())
    {
      return;
    }
  }
}

int main(int argc, char* argv[])
{
  auto start = std::chrono::high_resolution_clock::now();
  // get arguments
  if (argc != 3)
  {
    std::cout << "<vertices> <chunk size> /* get input from listg -Aq */" << std::endl;
    return EXIT_FAILURE;
  }
  int vertices = atoi(argv[1]);
  int chunkSize = atoi(argv[2]);

  TSQ<std::vector<Graph>> queue;

  std::vector<std::thread> workers;

  std::thread feeder([&]() { feedQueue(queue, vertices, chunkSize); });

  auto n = std::thread::hardware_concurrency();
  std::cout << n << " worker threads" << std::endl;

  std::string file;
  for (auto i = 0u; i < n; ++i)
  {
    file = "out" + std::to_string(i) + ".adj";
    std::ofstream fout(file);
    workers.emplace_back([&]() { processQueue(queue, vertices, fout); });
  }

  feeder.join();
  for (auto&& t : workers) t.join();

  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(end - start).count()
            << "milliseconds elapsed" << std::endl;
    return EXIT_SUCCESS;
}
