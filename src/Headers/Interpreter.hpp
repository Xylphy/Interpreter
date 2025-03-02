#pragma once

#include <cmath>

#include "Environment.hpp"
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
  auto visitLogicalExpr(const Logical& Expr) -> void override;

  auto visitExpressionStmt(const Expression& Stmt) -> void override;
  auto visitPrintStmt(const Print& Stmt) -> void override;
  auto visitVarStmt(const Var& Stmt) -> void override;
  auto visitBlockStmt(const Block& Stmt) -> void override;
  auto visitIfStmt(const If& Stmt) -> void override;
  auto visitWhileStmt(const While& Stmt) -> void override;

  auto execute(Stmt* statement) -> void;
  auto executeBlock(const std::vector<Stmt*>& statements, Environment* env)
      -> void;
  auto setPrintResult(Expr* expr) -> void;
  auto setInterpretResult(Expr* expr) -> void;
  auto setResult(std::any& toSet, const std::any& toGet, TokenType type)
      -> void;

  [[nodiscard]] auto getResult() const -> std::any;

  template <typename T, typename U>
  static auto addNumerics(const T& left, const U& right)
      -> decltype(left + right) {
    return left + right;
  }

  template <typename T, typename U>
  static auto subtractNumerics(const T& left, const U& right)
      -> decltype(left - right) {
    return left - right;
  }

  template <typename T, typename U>
  static auto multiplyNumerics(const T& left, const U& right)
      -> decltype(left * right) {
    return left * right;
  }

  template <typename T, typename U>
  static auto divideNumerics(const T& left, const U& right)
      -> decltype(left / right) {
    try {
      return left / right;
    } catch (const std::exception& e) {
      throw std::runtime_error("Division by zero");
    }
  }

  template <typename T, typename U>
  static auto moduloNumerics(const T& left, const U& right)
      -> decltype(left % right) {
    return left % right;
  }

  template <typename T, typename U>
  static auto greaterThan(const T& left, const U& right) -> bool {
    return left > right;
  }

  template <typename T, typename U>
  static auto greaterThanOrEqual(const T& left, const U& right) -> bool {
    return left >= right;
  }

  template <typename T, typename U>
  static auto lessThan(const T& left, const U& right) -> bool {
    return left < right;
  }

  template <typename T, typename U>
  static auto lessThanOrEqual(const T& left, const U& right) -> bool {
    return left <= right;
  }

  template <typename T, typename U>
  static auto notEqual(const T& left, const U& right) -> bool {
    return left != right;
  }

  template <typename T, typename U>
  static auto equal(const T& left, const U& right) -> bool {
    return left == right;
  }

  // This function checks if the operation is valid for the given operands.

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"

  template <typename leftDataType, typename rightDataType>
  static auto numericOperation(const leftDataType& left, TokenType type,
                               const rightDataType& right) -> std::any {
    bool newResult;
    std::any tempResult;
    switch (type) {
      case TokenType::GREATER:
        return greaterThan(left, right);
      case TokenType::GREATER_EQUAL:
        return greaterThanOrEqual(left, right);
      case TokenType::LESS:
        return lessThan(left, right);
      case TokenType::LESS_EQUAL:
        return lessThanOrEqual(left, right);
      case TokenType::BANG_EQUAL:
        return notEqual(left, right);
      case TokenType::EQUAL_EQUAL:
        return equal(left, right);
      case TokenType::MINUS:
        return subtractNumerics(left, right);
      case TokenType::PLUS:
        return addNumerics(left, right);
      case TokenType::SLASH:
        return divideNumerics(left, right);
      case TokenType::STAR:
        return multiplyNumerics(left, right);
      case TokenType::MODULO:
        if constexpr (std::is_integral_v<leftDataType> &&
                      std::is_integral_v<rightDataType>) {
          return moduloNumerics(left, right);
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