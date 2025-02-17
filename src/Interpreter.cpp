#include "Headers/Interpreter.hpp"

auto Interpreter::evaluate(Expr* expression) -> std::any {
  return expression->accept(*this);
}

auto Interpreter::visitBinaryExpr(const Binary& Expr) -> std::string { return Expr.value; }

auto Interpreter::visitGroupingExpr(const Grouping& Expr) -> std::string {
  return std::any_cast<std::string>(evaluate(Expr.expression));
}

auto Interpreter::visitLiteralExpr(const Literal& Expr) -> std::string {}

auto Interpreter::visitUnaryExpr(const Unary& Expr) -> std::string {
  std::any right = evaluate(Expr.right);

  switch (Expr.op.type) {
    case TokenType::MINUS:
      return -std::any_cast<double>(right);
      /*     case TokenType::BANG:
            return "!" + right;
          default:
            return ""; */
  }

  return {};
}
