#include <iostream>
#include <string>

#include "Headers/bisayaPP.hpp"

auto main() -> int {
  std::string path;
  std::cout << "Enter path to file: ";
  std::getline(std::cin, path);
  return BisayaPP::runFile(path.c_str());
}
