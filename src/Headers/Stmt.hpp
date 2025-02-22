#pragma once

#include "Expr.hpp"

class Expression;
class Print;
class Var;

class StmtVisitor {
 public:
  virtual auto visitExpressionStmt(const Expression &Stmt) -> void = 0;
  virtual auto visitPrintStmt(const Print &Stmt) -> void = 0;
  virtual auto visitVarStmt(const Var &Stmt) -> void = 0;
  virtual ~StmtVisitor() = default;
};

class Stmt {
 public:
  virtual ~Stmt() = default;
  virtual auto accept(StmtVisitor &visitor) -> void = 0;
};

class Expression : public Stmt {
 public:
  Expr *expression;

  Expression(Expr *expression) : expression(expression) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitExpressionStmt(*this);
  }
};

class Print : public Stmt {
 public:
  Expr *expression;

  Print(Expr *expression) : expression(expression) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitPrintStmt(*this);
  }
};

class Var : public Stmt {
 public:
  Token name;
  Expr *initializer;

  Var(Token name, Expr *initializer) : name(name), initializer(initializer) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitVarStmt(*this);
  }
};
