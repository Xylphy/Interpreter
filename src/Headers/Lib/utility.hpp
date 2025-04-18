#pragma once

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
auto isConvertibleToString(const std::any& value) -> bool;
auto checkValidOperation(const std::any& left, TokenType type,
                         const std::any& right) -> bool;
auto isAlpha(char character) noexcept -> bool;
auto isAlphaNumeric(char character) noexcept -> bool;
auto isDigit(char character) noexcept -> bool;
auto validAssignment(const TokenType& tokenType) -> bool;
auto checkNumberOperands(const TokenType& left, const Token& token,
                         const TokenType& right) -> void;
auto checkNumberOperand(const Token& token, TokenType operand) -> void;
auto checkNumberOperand(const TokenType& tokenType) -> void;
auto isTruthy(const std::any& value) -> bool;
auto isDataType(const TokenType& type) -> bool;
auto isLiterals(const TokenType& type) -> bool;
auto typeEquality(VariableTokenType variableType, LiteralTokenType literalType) -> bool;
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

template <typename leftDataType, typename rightDataType>
static auto numericOperation(const leftDataType& left, TokenType type,
                             const rightDataType& right) -> std::any {
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
    default:
      throw std::runtime_error("Invalid operation");
  }
}

}  // namespace utility