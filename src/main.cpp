#include <iostream>
#include <string>

#include "Headers/AstPrinter.hpp"
#include "Headers/bisayaPP.hpp"

auto main() -> int {
  std::string path;
  std::cout << "Enter path to file: ";
  std::getline(std::cin, path);
  BisayaPP::runFile(path.c_str());

  return 0;
}
