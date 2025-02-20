#pragma once
#include "Expr.hpp"
#include "Token.hpp"

class Interpreter : public ExprVisitor {
 public:
  auto evaluate(Expr* expression) -> bool;

 private:
  auto visitBinaryExpr(const Binary& Expr) -> void override;
  auto visitGroupingExpr(const Grouping& Expr) -> void override;
  auto visitLiteralExpr(const Literal& Expr) -> void override;
  auto visitUnaryExpr(const Unary& Expr) -> void override;
  auto setPrintResult(Expr* expr) -> void;
  auto setInterpretResult(Expr* expr) -> void;
  auto setResult(std::any& toSet, const std::any& toGet, TokenType type)
      -> void;
  static auto checkNumberOperands(const Token& token, TokenType left,
                                  TokenType right) -> void;
  static auto checkNumberOperand(const Token& token, TokenType operand) -> void;
  static auto isTruthy(const std::any& value, TokenType type) -> bool;
  static auto stringify(std::any& value) -> std::string;
  [[nodiscard]] auto getResult() const -> std::any;
  TokenType type;
  std::any result;
};