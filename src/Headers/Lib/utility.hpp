#pragma once

#include <sys/types.h>

#include <cmath>
#include <string>

#include "../Token.hpp"  // IWYU pragma: export

// This namespace contains utility functions that are used in the project.
namespace utility {

struct LiteralTokenType {
  TokenType type;
};

struct VariableTokenType {
  TokenType type;
};

auto anyToString(std::string& result, const std::any& value) noexcept -> void;
auto anyToString(const std::any& value) noexcept -> std::string;
auto convertData(const TokenType& type, std::any& value) -> void;
auto isArithmetic(const std::any& value) -> bool;
auto isCharacter(const std::any& value) -> bool;
auto isConvertibleToString(const std::any& value) -> bool;
auto checkValidOperation(const std::any& left, TokenType type,
                         const std::any& right) -> bool;
auto isAlpha(char character) noexcept -> bool;
auto isAlphaNumeric(char character) noexcept -> bool;
auto isDigit(char character) noexcept -> bool;
auto validAssignment(const TokenType& tokenType) -> bool;
auto checkOperands(const TokenType& left, const Token& token,
                   const TokenType& right) -> void;
auto checkOperand(const TokenType& tokenType) -> void;
auto isTruthy(const std::any& value) -> bool;
auto isDataType(const TokenType& type) -> bool;
auto isLiterals(const TokenType& type) -> bool;
auto typeEquality(VariableTokenType variableType, LiteralTokenType literalType)
    -> bool;
auto typeToLiteralType(const TokenType& type) -> TokenType;

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

template <typename Left, typename Right>
  requires(std::same_as<Left, int> || std::same_as<Left, double>) &&
          (std::same_as<Right, int> || std::same_as<Right, double>)
auto doOperation(const Left& left, TokenType type, const Right& right)
    -> std::any {
  switch (type) {
    case TokenType::BANG_EQUAL:
      return notEqual(left, right);
    case TokenType::EQUAL_EQUAL:
      return equal(left, right);
    case TokenType::GREATER:
      return greaterThan(left, right);
    case TokenType::GREATER_EQUAL:
      return greaterThanOrEqual(left, right);
    case TokenType::LESS:
      return lessThan(left, right);
    case TokenType::LESS_EQUAL:
      return lessThanOrEqual(left, right);
    case TokenType::MINUS:
      return subtractNumerics(left, right);
    case TokenType::PLUS:
      return addNumerics(left, right);
    case TokenType::SLASH:
      return divideNumerics(left, right);
    case TokenType::STAR:
      return multiplyNumerics(left, right);
    case TokenType::MODULO:
      if constexpr (std::is_integral_v<Left> && std::is_integral_v<Right>) {
        return moduloNumerics(left, right);
      } else {
        return std::fmod(left, right);
      }
    case TokenType::CONCATENATOR:
      return std::to_string(left).append(std::to_string(right));
    default:
      throw std::runtime_error("Invalid operation");
  }
}

template <typename Left, typename Right>
  requires(std::same_as<Left, char> &&
           (std::same_as<Right, int> || std::same_as<Right, double>)) ||
          ((std::same_as<Left, int> || std::same_as<Left, double>) &&
           std::same_as<Right, char>)
auto doOperation(const Left& left, TokenType operation, const Right& right)
    -> std::any {
  switch (operation) {
    case TokenType::BANG_EQUAL:
      return notEqual(left, right);
    case TokenType::EQUAL_EQUAL:
      return equal(left, right);
    case TokenType::GREATER:
      return greaterThan(left, right);
    case TokenType::GREATER_EQUAL:
      return greaterThanOrEqual(left, right);
    case TokenType::LESS:
      return lessThan(left, right);
    case TokenType::LESS_EQUAL:
      return lessThanOrEqual(left, right);
    case TokenType::CONCATENATOR:
      if constexpr (std::is_same_v<Left, char>) {
        return std::string(1, left).append(std::to_string(right));
      } else {
        return std::to_string(left).append(1, right);
      }
    default:
      throw std::runtime_error("Invalid operation");
  }
}

auto doOperation(const char& left, TokenType operation, const char& right)
    -> std::any;

void doOperation(TokenType& leftType, std::any& left, TokenType& rightType,
                 std::any& right, std::any& tempResult,
                 const TokenType& exprTokenType);
}  // namespace utility