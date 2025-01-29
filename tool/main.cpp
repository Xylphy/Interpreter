#include <iostream>

#include "generateAst.h"

int main(int argc, char *argv[]) {
	if (argc != 1) {
		std::cout << "Usage: " << argv[0] << std::endl;
		exit(64);
	}

	defineAst(argv[0], "Stmt",
			  {
				  "If : std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> "
				  "thenBranch, std::unique_ptr<Stmt> elseBranch",
				  "While : std::unique_ptr<Expr> condition, "
				  "std::unique_ptr<Stmt> body",
				  "Block      : std::vector<std::unique_ptr<Stmt>> statements",
				  "Break",
				  "Expression : std::unique_ptr<Expr> expression",
				  "Print      : std::unique_ptr<Expr> expression",
				  "Var        : Token name, std::unique_ptr<Expr> initializer",
				  "Function   : Token name, std::vector<Token> params, "
				  "std::vector<std::unique_ptr<Stmt>> body",
			  });
	return 0;
}