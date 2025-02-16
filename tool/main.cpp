#include <iostream>

#include "generateAst.hpp"

const int USAGE_ERROR_CODE = 64;

auto main(int argc, char *argv[]) -> int {
  if (argc != 1) {
    std::cout << "Usage: " << "Abstract Syntax Tree" << '\n';
    exit(USAGE_ERROR_CODE);
  }

  defineAst("Headers", "Expr",
            {"Binary: Expr *left, Token op, Expr *right",
             "Grouping: Expr *expression", "Literal: std::any value",
             "Unary: Token op, Expr *right"});
  return 0;
}