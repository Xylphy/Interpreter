#pragma once
#include <cmath>
#include <vector>

#include "Environment.hpp"
#include "Lib/utility.hpp"
#include "Stmt.hpp"

class Interpreter : public ExprVisitor, public StmtVisitor {
 public:
  Interpreter();
  auto evaluate(Expr* expression) -> bool;
  auto setInterpretResult(const std::vector<Stmt*>& statements) -> void;

 private:
  auto visitBinaryExpr(const Binary& Expr) -> void override;
  auto visitGroupingExpr(const Grouping& Expr) -> void override;
  auto visitLiteralExpr(const Literal& Expr) -> void override;
  auto visitUnaryExpr(const Unary& Expr) -> void override;
  auto visitVariableExpr(const Variable& Expr) -> void override;
  auto visitAssignExpr(const Assign& Expr) -> void override;

  auto visitExpressionStmt(const Expression& Stmt) -> void override;
  auto visitPrintStmt(const Print& Stmt) -> void override;
  auto visitVarStmt(const Var& Stmt) -> void override;
  auto visitBlockStmt(const Block& Stmt) -> void override;

  auto execute(Stmt* statement) -> void;
  auto executeBlock(const std::vector<Stmt*>& statements, Environment* env)
      -> void;
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
  Environment* environment;
  TokenType type;
  std::any result;
};