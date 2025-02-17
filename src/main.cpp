#include <cstdlib>
#include <iostream>

#include "Headers/AstPrinter.hpp"
#include "Headers/bisayaPP.hpp"

auto main() -> int {
  int choice;
  std::cout << "Enter 1 to run file or 2 to run prompt: ";
  std::cin >> choice;
  std::string path;

  switch (choice) {
    case 1:
      std::cout << "Enter path to file: ";
      std::cin >> path;
      BisayaPP::runFile(path.c_str());
      break;
    case 2:
      BisayaPP::runPrompt();
      break;
    default:
      std::cout << "Invalid choice" << '\n';
      break;
  }

  /* 	Expr* expression = new Binary(
                      new Unary(Token(TokenType::MINUS, "-", "", 1), new
     Literal(123)), Token(TokenType::STAR, "*", "", 1), new Grouping(new
     Literal(45.67))
              );
              AstPrinter printer;

              std::cout << printer.print(expression) << std::endl; */
  return 0;
}
