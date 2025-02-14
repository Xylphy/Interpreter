#include "Headers/AstPrinter.hpp"

#include <typeinfo>

#include "Headers/Expr.hpp"
#include "Headers/Token.hpp"

std::string AstPrinter::visitBinaryExpr(const Binary &Expr) {
	return parenthesize(Expr.op.lexeme, {Expr.left, Expr.right});
}

std::string AstPrinter::visitGroupingExpr(const Grouping &Expr) {
	return parenthesize("group", {Expr.expression});
}

std::string AstPrinter::visitLiteralExpr(const Literal &Expr) {
	if (Expr.value.has_value()) {
		if (Expr.value.type() == typeid(int)) {
			return std::to_string(std::any_cast<int>(Expr.value));
		} else if (Expr.value.type() == typeid(double)) {
			return std::to_string(std::any_cast<double>(Expr.value));
		} else if (Expr.value.type() == typeid(std::string)) {
			return std::any_cast<std::string>(Expr.value);
		} else if (Expr.value.type() == typeid(char)) {
			return std::string(1, std::any_cast<char>(Expr.value));
        }
	}
    return "nil";
}

std::string AstPrinter::visitUnaryExpr(const Unary &Expr) {
	return parenthesize(Expr.op.lexeme, {Expr.right});
}

std::string AstPrinter::print(Expr *expr) { return expr->accept(*this); }

std::string AstPrinter::parenthesize(std::string name,
									 std::initializer_list<Expr *> exprs) {
	std::string res;
	for (Expr *expr : exprs) {
		res += " ";
		res += expr->accept(*this);
	}

	return "(" + name + res + ")";
}