#include <iostream>

#include "generateAst.hpp"

int main(int argc, char *argv[]) {
	if (argc != 1) {
		std::cout << "Usage: " << "Abstract Syntax Tree" << std::endl;
		exit(64);
	}

	defineAst("Headers", "Expr",
			  {"Binary: Expr *left, Token op, Expr *right",
			   "Grouping: Expr *expression", "Literal: std::any value",
			   "Unary: Token op, Expr *right"});
	return 0;
}