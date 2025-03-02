#include <cstdlib>
#include <iostream>

#include "Headers/AstPrinter.hpp"
#include "Headers/bisayaPP.hpp"

auto main() -> int {
  std::string path;
  std::cout << "Enter path to file: ";
  std::cin >> path;
  BisayaPP::runFile(path.c_str());

  return 0;
}
