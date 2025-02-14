#pragma once

#include "../Token.hpp"
#include "Expr.hpp"

class Binary;
class Grouping;
class Literal;
class Unary;

class StmtVisitor {
   public:
	virtual void visitBinaryStmt(const Binary &Stmt) = 0;
	virtual void visitGroupingStmt(const Grouping &Stmt) = 0;
	virtual void visitLiteralStmt(const Literal &Stmt) = 0;
	virtual void visitUnaryStmt(const Unary &Stmt) = 0;
};

class Stmt {
   public:
	virtual ~Stmt() = default;
	virtual void accept(StmtVisitor &visitor) = 0;
};

class Binary : public Stmt {
   public:
	Expr *left;
	Token op;
	Expr *right;

	Binary(Expr *left, Token op, Expr *right)
		: left(left), op(op), right(right) {}

	void accept(StmtVisitor &visitor) override {
		visitor.visitBinaryStmt(*this);
	}
};

class Grouping : public Stmt {
   public:
	Expr *expression;

	Grouping(Expr *expression) : expression(expression) {}

	void accept(StmtVisitor &visitor) override {
		visitor.visitGroupingStmt(*this);
	}
};

class Literal : public Stmt {
   public:
	std::any value;

	Literal(std::any value) : value(value) {}

	void accept(StmtVisitor &visitor) override {
		visitor.visitLiteralStmt(*this);
	}
};

class Unary : public Stmt {
   public:
	Token op;
	Expr *right;

	Unary(Token op, Expr *right) : op(op), right(right) {}

	void accept(StmtVisitor &visitor) override {
		visitor.visitUnaryStmt(*this);
	}
};
