int main(int argc, char* argv[])
{
  int vertices = 0;
  std::string file;

  // get arguments
  if (argc != 3)
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
  std::ofstream fout("nonExtendable.g6");
  int start_s = clock();
  auto graphs = read(vertices, file);
  process(vertices, graphs, fout);
  int stop_s = clock();
  std::cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000
            << std::endl;
}
