#include <iostream>

#include "generateAst.hpp"

const int USAGE_ERROR_CODE = 64;

auto main(int argc, char *argv[]) -> int {
  if (argc != 1) {
    std::cout << "Usage: " << "Abstract Syntax Tree" << '\n';
    exit(USAGE_ERROR_CODE);
  }

  defineAst(
      "Headers", "Stmt",
      {"Block: std::vector<Stmt*> statements",
       "Expression: std::unique_ptr<Expr> expression",
       "If: std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> thenBranch, std::unique_ptr<Stmt> elseBranch",
       "Print: std::unique_ptr<Expr> expression",
       "Var: Token name, std::unique_ptr<Expr> initializer",
       "While: std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> body",
       "Input: std::vector<Token> variables, std::vector<Token> inputs"});

  // defineAst(
  //     "Headers", "Expr",
  //     {"Assign: Token name, std::unique_ptr<Expr> value",
  //      "Binary: std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr>
  //      right", "Grouping: std::unique_ptr<Expr> expression", "Literal:
  //      std::any value, TokenType type", "Logical: std::unique_ptr<Expr> left,
  //      Token op, std::unique_ptr<Expr> right", "Unary: Token op,
  //      std::unique_ptr<Expr> right", "Variable: Token name"});
  return 0;
}