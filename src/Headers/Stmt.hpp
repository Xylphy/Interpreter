#pragma once

#include <utility>
#include <vector>

#include "Expr.hpp"

class Block;
class Expression;
class If;
class Print;
class Var;
class While;
class Input;

class StmtVisitor {
 public:
  virtual auto visitBlockStmt(const Block &Stmt) -> void = 0;
  virtual auto visitExpressionStmt(const Expression &Stmt) -> void = 0;
  virtual auto visitIfStmt(const If &Stmt) -> void = 0;
  virtual auto visitPrintStmt(const Print &Stmt) -> void = 0;
  virtual auto visitVarStmt(const Var &Stmt) -> void = 0;
  virtual auto visitWhileStmt(const While &Stmt) -> void = 0;
  virtual auto visitInputStmt(const Input &Stmt) -> void = 0;
  virtual ~StmtVisitor() = default;
};

class Stmt {
 public:
  virtual ~Stmt() = default;
  virtual auto accept(StmtVisitor &visitor) -> void = 0;
};

class Block : public Stmt {
 public:
  std::vector<Stmt *> statements;

  Block(std::vector<Stmt *> statements) : statements(std::move(statements)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitBlockStmt(*this);
  }

  ~Block() override = default;
};

class Expression : public Stmt {
 public:
  Expr *expression;

  Expression(Expr *expression) : expression(expression) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitExpressionStmt(*this);
  }

  ~Expression() override { delete expression; }
};

class If : public Stmt {
 public:
  Expr *condition;
  Stmt *thenBranch;
  Stmt *elseBranch;

  If(Stmt *thenBranch, Expr *condition, Stmt *elseBranch)
      : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitIfStmt(*this);
  }

  ~If() override {
    delete condition;
    delete thenBranch;
    delete elseBranch;
  }
};

class Print : public Stmt {
 public:
  Expr *expression;

  Print(Expr *expression) : expression(expression) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitPrintStmt(*this);
  }

  ~Print() override { delete expression; }
};

class Var : public Stmt {
 public:
  Token name;
  Expr *initializer;

  Var(Token name, Expr *initializer)
      : name(std::move(name)), initializer(initializer) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitVarStmt(*this);
  }

  ~Var() override { delete initializer; }
};

class While : public Stmt {
 public:
  Expr *condition;
  Stmt *body;

  While(Expr *condition, Stmt *body) : condition(condition), body(body) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitWhileStmt(*this);
  }

  ~While() override {
    delete condition;
    delete body;
  }
};

class Input : public Stmt {
 public:
  std::vector<Token> variables;

  Input(std::vector<Token> variables) : variables(std::move(variables)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitInputStmt(*this);
  }

  ~Input() override = default;
};
