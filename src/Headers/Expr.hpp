#pragma once

#include "Token.hpp"
class Binary;
class Grouping;
class Literal;
class Unary;

class ExprVisitor {
   public:
	virtual std::string visitBinaryExpr(const Binary &Expr) = 0;
	virtual std::string visitGroupingExpr(const Grouping &Expr) = 0;
	virtual std::string visitLiteralExpr(const Literal &Expr) = 0;
	virtual std::string visitUnaryExpr(const Unary &Expr) = 0;
};

class Expr {
   public:
	virtual ~Expr() = default;
	virtual std::string accept(ExprVisitor &visitor) = 0;
};

class Binary : public Expr {
   public:
	Expr *left;
	Token op;
	Expr *right;

	Binary(Expr *left, Token op, Expr *right)
		: left(left), op(op), right(right) {}

	std::string accept(ExprVisitor &visitor) override {
		return visitor.visitBinaryExpr(*this);
	}
};

class Grouping : public Expr {
   public:
	Expr *expression;

	Grouping(Expr *expression) : expression(expression) {}

	std::string accept(ExprVisitor &visitor) override {
		return visitor.visitGroupingExpr(*this);
	}
};

class Literal : public Expr {
   public:
	std::any value;

	Literal(std::any value) : value(value) {}

	std::string accept(ExprVisitor &visitor) override {
		return visitor.visitLiteralExpr(*this);
	}
};

class Unary : public Expr {
   public:
	Token op;
	Expr *right;

	Unary(Token op, Expr *right) : op(op), right(right) {}

	std::string accept(ExprVisitor &visitor) override {
		return visitor.visitUnaryExpr(*this);
	}
};
