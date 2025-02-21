#pragma once
#include <cmath>

#include "Expr.hpp"
#include "Lib/utility.hpp"
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"

  template <typename leftDataType, typename rightDataType>
  static auto numericOperation(const leftDataType& left, TokenType type,
                               const rightDataType& right) -> std::any {
    bool newResult;
    std::any tempResult;
    switch (type) {
      case TokenType::GREATER:
        return utility::greaterThan(left, right);
      case TokenType::GREATER_EQUAL:
        return utility::greaterThanOrEqual(left, right);
      case TokenType::LESS:
        return utility::lessThan(left, right);
      case TokenType::LESS_EQUAL:
        return utility::lessThanOrEqual(left, right);
      case TokenType::BANG_EQUAL:
        return utility::notEqual(left, right);
      case TokenType::EQUAL_EQUAL:
        return utility::equal(left, right);
      case TokenType::MINUS:
        return utility::subtractNumerics(left, right);
      case TokenType::PLUS:
        return utility::addNumerics(left, right);
      case TokenType::SLASH:
        return utility::divideNumerics(left, right);
      case TokenType::STAR:
        return utility::multiplyNumerics(left, right);
      case TokenType::MODULO:
        if constexpr (std::is_integral_v<leftDataType> &&
                      std::is_integral_v<rightDataType>) {
          return utility::moduloNumerics(left, right);
        } else {
          return std::fmod(left, right);
        }
      case TokenType::CONCATENATOR:
        return std::to_string(left).append(std::to_string(right));
    }
    throw std::runtime_error("Invalid operation");
  }

#pragma clang diagnostic pop

  [[nodiscard]] auto getResult() const -> std::any;
  TokenType type;
  std::any result;
};