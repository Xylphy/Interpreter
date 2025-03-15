#pragma once

#include <any>
#include <memory>

#include "Environment.hpp"
#include "Stmt.hpp"

class Interpreter : public ExprVisitor, public StmtVisitor {
 public:
  auto evaluate(Expr* expression) -> bool;
  auto setInterpretResult(const std::vector<std::unique_ptr<Stmt>>& statements)
      -> void;

 private:
  auto visitBinaryExpr(const Binary& Expr) -> void override;
  auto visitGroupingExpr(const Grouping& Expr) -> void override;
  auto visitLiteralExpr(const Literal& Expr) -> void override;
  auto visitUnaryExpr(const Unary& Expr) -> void override;
  auto visitVariableExpr(const Variable& Expr) -> void override;
  auto visitAssignExpr(const Assign& Expr) -> void override;
  auto visitLogicalExpr(const Logical& Expr) -> void override;

  auto visitExpressionStmt(const Expression& Stmt) -> void override;
  auto visitPrintStmt(const Print& Stmt) -> void override;
  auto visitInputStmt(const Input& Stmt) -> void override;
  auto visitVarStmt(const Var& Stmt) -> void override;
  auto visitBlockStmt(const Block& Stmt) -> void override;
  auto visitIfStmt(const If& Stmt) -> void override;
  auto visitWhileStmt(const While& Stmt) -> void override;

  auto execute(const std::unique_ptr<Stmt>& statement) -> void;
  auto executeBlock(const std::vector<Stmt*>& statements,
                    std::shared_ptr<Environment>&& env) -> void;
  auto setPrintResult(Expr* expr) -> void;
  auto setInterpretResult(Expr* expr) -> void;
  auto setResult(std::any& toSet, const std::any& toGet, TokenType type)
      -> void;

  [[nodiscard]] auto getResult() const -> std::any;

  std::shared_ptr<Environment> environment;
  TokenType type;
  std::any result;
};