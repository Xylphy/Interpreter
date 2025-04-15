#pragma once

#include "Environment.hpp"
#include "Expr.hpp"
#include "Stmt.hpp"

class Interpreter : public ExprVisitor, public StmtVisitor {
 public:
  Interpreter();

  auto evaluate(const std::unique_ptr<Expr>& expression) -> bool;
  auto setInterpretResult(const std::vector<std::unique_ptr<Stmt>>& statements)
      -> void;

  // Resets the interpreter state
  // Used especially where the interpreter is tested against multiple test cases
  // and must be resetted for each test case
  void resetInterpreter();

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
  auto executeBlock(const std::vector<std::unique_ptr<Stmt>>& statements,
                    std::shared_ptr<Environment>&& env) -> void;
  auto setPrintResult(const std::unique_ptr<Expr>& expr) -> void;
  auto setInterpretResult(const std::unique_ptr<Expr>& expr) -> void;
  auto setResult(std::any& toSet, const std::any& toGet, TokenType tokenType)
      -> void;

  [[nodiscard]] auto getResult() const -> std::any;

  std::shared_ptr<Environment> environment;
  TokenType type;
  std::any result;
};