#include "Binary.hpp"

Binary::Binary(Expr *left, Token op, Expr *right)
	: op(op), left(left), right(right) {}