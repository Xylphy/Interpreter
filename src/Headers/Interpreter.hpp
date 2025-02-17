#pragma once
#include "Expr.hpp"

class Interpreter : public ExprVisitor {
 public:
  auto visitBinaryExpr(const Binary& Expr) -> std::string override;
  auto visitGroupingExpr(const Grouping& Expr) -> std::string override;
  auto visitLiteralExpr(const Literal& Expr) -> std::string override;
  auto visitUnaryExpr(const Unary& Expr) -> std::string override;

 private:
  auto evaluate(Expr* expression) -> std::any;
};