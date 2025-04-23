#pragma once

#include <memory>
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
};

class Stmt {
 public:
  virtual ~Stmt() = default;
  virtual auto accept(StmtVisitor &visitor) -> void = 0;
};

class Block : public Stmt {
 public:
  std::vector<std::unique_ptr<Stmt>> statements;

  Block(std::vector<std::unique_ptr<Stmt>> &&statements)
      : statements(std::move(statements)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitBlockStmt(*this);
  }
};

class Expression : public Stmt {
 public:
  std::unique_ptr<Expr> expression;

  Expression(std::unique_ptr<Expr> &&expression)
      : expression(std::move(expression)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitExpressionStmt(*this);
  }
};

class If : public Stmt {
 public:
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Stmt> thenBranch;
  std::unique_ptr<Stmt> elseBranch;

  If(std::unique_ptr<Expr> &&condition, std::unique_ptr<Stmt> &&thenBranch,
     std::unique_ptr<Stmt> &&elseBranch)
      : condition(std::move(condition)),
        thenBranch(std::move(thenBranch)),
        elseBranch(std::move(elseBranch)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitIfStmt(*this);
  }
};

class Print : public Stmt {
 public:
  std::unique_ptr<Expr> expression;

  Print(std::unique_ptr<Expr> &&expression)
      : expression(std::move((expression))) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitPrintStmt(*this);
  }
};

class Var : public Stmt {
 public:
  Token name;
  std::unique_ptr<Expr> initializer;

  Var(const Token &name, std::unique_ptr<Expr> &&initializer)
      : name(name), initializer(std::move(initializer)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitVarStmt(*this);
  }
};

class While : public Stmt {
 public:
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Stmt> body;

  While(std::unique_ptr<Expr> &&condition, std::unique_ptr<Stmt> &&body)
      : condition(std::move(condition)), body(std::move(body)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitWhileStmt(*this);
  }
};

class Input : public Stmt {
 public:
  std::vector<Token> tokens;

  Input(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

  auto accept(StmtVisitor &visitor) -> void override {
    visitor.visitInputStmt(*this);
  }
};
