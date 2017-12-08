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
        std::cerr << '\n' << "END OF STDIN" << std::endl;
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

void processQueue(TSQ<std::vector<Graph>>& queue, int vertices, std::string file, int id)
{
  std::ofstream fout(file);
  if (!fout) std::cerr << id << " FILE NOT OPEN!" << std::endl;
  std::vector<Graph> graphs;
  for (;;)
  {
    if (queue.dequeue(graphs))
    {
      process(vertices, graphs, fout);
    }
    else if (!queue.hasMore())
    {
      fout.close();
      return;
    }
  }
}

int main(int argc, char* argv[])
{
  auto start = std::chrono::high_resolution_clock::now();
  // get arguments
  if (argc < 3)
  {
    std::cerr << "<vertices> <chunk size> [n threads] /* get input from listg -Aq */"
              << std::endl;
    return EXIT_FAILURE;
  }
  auto n = 0u;
  if (argc > 3)
    n = atoi(argv[3]);
  else
    n = std::thread::hardware_concurrency();
  std::cerr << n << " worker threads" << std::endl;

  static int vertices = atoi(argv[1]);
  static int chunkSize = atoi(argv[2]);

  TSQ<std::vector<Graph>> queue;

  std::vector<std::thread> workers;

  std::thread feeder([&]() { feedQueue(queue, vertices, chunkSize); });

  for (auto i = 0u; i < n; ++i)
  {
    const std::string file = "out" + std::to_string(i) + ".adj";
    std::cerr << i << " " << file << std::endl;
    // workers.push_back(std::thread([&queue, vertices, file, i]() { processQueue(queue,
    // vertices, file, i); }));
    workers.emplace_back(processQueue, std::ref(queue), vertices, file, i);
  }

  feeder.join();
  for (auto&& t : workers) t.join();

  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(end - start).count()
            << "milliseconds elapsed" << std::endl;
  return EXIT_SUCCESS;
}
