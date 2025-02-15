/* #pragma once

#include "Expr.hpp"
#include "Token.hpp"

class Binary;
class Grouping;
class Literal;
class Unary;

class StmtVisitor {
   public:
	virtual std::string visitBinaryStmt(const Binary &Stmt) = 0;
	virtual std::string visitGroupingStmt(const Grouping &Stmt) = 0;
	virtual std::string visitLiteralStmt(const Literal &Stmt) = 0;
	virtual std::string visitUnaryStmt(const Unary &Stmt) = 0;
};

class Stmt {
   public:
	virtual ~Stmt() = default;
	virtual std::string accept(StmtVisitor &visitor) = 0;
};

class Binary : public Stmt {
   public:
	Expr *left;
	Token op;
	Expr *right;

	Binary(Expr *left, Token op, Expr *right)
		: left(left), op(op), right(right) {}

	std::string accept(StmtVisitor &visitor) override {
		return visitor.visitBinaryStmt(*this);
	}
};

class Grouping : public Stmt {
   public:
	Expr *expression;

	Grouping(Expr *expression) : expression(expression) {}

	std::string accept(StmtVisitor &visitor) override {
		return visitor.visitGroupingStmt(*this);
	}
};

class Literal : public Stmt {
   public:
	std::any value;

	Literal(std::any value) : value(value) {}

	std::string accept(StmtVisitor &visitor) override {
		return visitor.visitLiteralStmt(*this);
	}
};

class Unary : public Stmt {
   public:
	Token op;
	Expr *right;

	Unary(Token op, Expr *right) : op(op), right(right) {}

	std::string accept(StmtVisitor &visitor) override {
		return visitor.visitUnaryStmt(*this);
	}
};
 */