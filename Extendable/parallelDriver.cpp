#include "cxxopts.hpp"
#include "cycleFinder.cpp"
#include "threadSafeQueue.hpp"
#include <chrono>
#include <csignal>
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

TSQ<std::vector<Graph>>* queuePointer;
void signalHandler(int signum)
{
  std::cout << "Interrupt signal (" << signum << ") received.\n";

  // cleanup and close up stuff here

  // terminate program
  exit(signum);
}

int main(int argc, char* argv[])
{
  int maxQueueSize, numThreads;
  static int vertices, chunkSize;

  // BEGIN command line args
  try
  {
    cxxopts::Options options(
      argv[0],
      "\nNot Extendable Parallel\nReads graphs in adjacency "
      "matricies from stdin. Determines whether graphs are not they are cycle "
      "extendable.\n\n");
    options.positional_help("<verticies> <chunksize>");

    // clang-format off
    options.add_options()
    ("h,help", "Print help")
    ("m,maxsize", "limit the size of the queue of graphs", cxxopts::value<int>()->default_value(std::to_string(std::numeric_limits<int>::max())))
    ("t,threads", "number of worker threads to process graphs", cxxopts::value<int>()->default_value(std::to_string(std::thread::hardware_concurrency())))
    ("verticies", "number of verticies of the graphs being processed", cxxopts::value<int>())
    ("chunksize", "number of graphs given to a thread at a time", cxxopts::value<int>())
    ("rest","", cxxopts::value<std::vector<std::string>>())
    ; // clang-format on

    options.parse_positional({"verticies", "chunksize", "rest"});

    auto args = options.parse(argc, argv);

    if (args.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(EXIT_SUCCESS);
    }

    if (args.count("verticies"))
    {
      vertices = args["verticies"].as<int>();
    }
    else
    {
      std::cout << "required: verticies\n";
      std::cout << options.help() << std::endl;
      exit(EXIT_FAILURE);
    }

    if (args.count("chunksize"))
    {
      chunkSize = args["chunksize"].as<int>();
    }
    else
    {
      std::cout << "required: chunksize\n";
      std::cout << options.help() << std::endl;
      exit(EXIT_FAILURE);
    }

    maxQueueSize = args["m"].as<int>();
    numThreads = args["t"].as<int>();
  }
  catch (const cxxopts::OptionException& e)
  {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  } // END command line args

  std::signal(SIGINT, signalHandler); // setup signal handling

  /* display settings  */
  std::cout << vertices << " vertices\n";
  std::cout << numThreads << " worker threads\n";
  std::cout << chunkSize << " graphs per chunk\n";
  std::cout << maxQueueSize << " max queue size" << std::endl;

  /* start timer */
  auto start = std::chrono::high_resolution_clock::now();

  TSQ<std::vector<Graph>> queue;
  queuePointer = &queue;

  std::vector<std::thread> workers;

  std::thread feeder([&]() { feedQueue(queue, vertices, chunkSize); });

  for (auto i = 0; i < numThreads; ++i)
  {
    const std::string file = "out" + std::to_string(i) + ".adj";
    std::cerr << i << " " << file << std::endl;
    // workers.push_back(std::thread([&queue, vertices, file, i]() { processQueue(queue,
    // vertices, file, i); }));
    workers.emplace_back(processQueue, std::ref(queue), vertices, file, i);
  }

  feeder.join();
  for (auto&& t : workers) t.join();

  /* end timer */
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration<double, std::milli>(end - start).count()
            << "milliseconds elapsed" << std::endl;
  return EXIT_SUCCESS;
}
