#include "commands.h"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Error: Invalid arguments. Usage: " << argv[0] << " <filename>" << "\n";
    return 1;
  }

  try {
    std::vector<Polygon> figures = readShapesFromFile(argv[1]);
    processCommands(figures);
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
