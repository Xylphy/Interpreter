#include <iostream>

#include "generateAst.hpp"

const int USAGE_ERROR_CODE = 64;

auto main(int argc, char *argv[]) -> int {
  if (argc != 1) {
    std::cout << "Usage: " << "Abstract Syntax Tree" << '\n';
    exit(USAGE_ERROR_CODE);
  }

  defineAst("Headers", "Stmt",
            {"Block: std::vector<Stmt*> statements","Expression: Expr* expression", "Print: Expr* expression",
             "Var: Token name, Expr* initializer"});

  // defineAst(
  //     "Headers", "Expr",
  //     {"Assign: Token name, Expr *value",
  //      "Binary: Expr *left, Token op, Expr *right",
  //      "Grouping: Expr *expression", "Literal: std::any value, TokenType type",
  //      "Unary: Token op, Expr *right", "Variable: Token name"});
  return 0;
}