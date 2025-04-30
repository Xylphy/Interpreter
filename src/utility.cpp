#include "Headers/Lib/utility.hpp"

#include <functional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <utility>

#if defined(_MSC_VER)
#include <string>
#endif

#include "Headers/Errors.hpp"
#include "Headers/Token.hpp"

namespace utility {

auto anyToString(std::string& result, const std::any& value) noexcept -> void {
  result.append(anyToString(value));
}

auto anyToString(const std::any& value) noexcept -> std::string {
  const std::type_info& type = value.type();
  if (type == typeid(int)) {
    return std::to_string(std::any_cast<int>(value));
  }
  if (type == typeid(double)) {
    return std::to_string(std::any_cast<double>(value));
  }
  if (type == typeid(std::string)) {
    return std::any_cast<std::string>(value);
  }
  if (type == typeid(char)) {
    return {1, std::any_cast<char>(value)};
  }
  if (type == typeid(bool)) {
    return std::any_cast<bool>(value) ? "OO" : "DILI";
  }
  if (type == typeid(const char*)) {
    return std::any_cast<const char*>(value);
  }

  return {};
}

auto convertData(const TokenType& type, std::any& value) -> void {
  if (type == TokenType::NUMBER) {
    value = std::any_cast<int>(value);
  } else if (type == TokenType::DECIMAL_NUMBER) {
    value = std::any_cast<double>(value);
  } else if (type == TokenType::STRING_LITERAL) {
    value = std::any_cast<std::string>(value);
  } else if (type == TokenType::CHARACTER_LITERAL) {
    value = std::any_cast<char>(value);
  } else if (type == TokenType::BOOL) {
    value = std::any_cast<bool>(value);
  }
}

auto checkValidOperation(const std::any& left, TokenType type,
                         const std::any& right) -> bool {
  switch (type) {
    case TokenType::BANG_EQUAL:
    case TokenType::EQUAL_EQUAL:
      return (isCharacter(left) && isCharacter(right)) ||
             (isArithmetic(left) && isArithmetic(right));
    case TokenType::GREATER:
    case TokenType::GREATER_EQUAL:
    case TokenType::LESS:
    case TokenType::LESS_EQUAL:
    case TokenType::MINUS:
    case TokenType::PLUS:
    case TokenType::SLASH:
    case TokenType::STAR:
    case TokenType::MODULO:
      return isArithmetic(left) && isArithmetic(right);
    case TokenType::CONCATENATOR:
    case TokenType::NEW_LINE:
      return isConvertibleToString(left) && isConvertibleToString(right);
    default:
      return false;
  }
}

auto isConvertibleToString(const std::any& value) -> bool {
  const std::type_info& type = value.type();
  return isArithmetic(value) || type == typeid(std::string) ||
         type == typeid(char) || type == typeid(const char*) ||
         type == typeid(bool);
}

auto isArithmetic(const std::any& value) -> bool {
  const std::type_info& type = value.type();
  return type == typeid(int) || type == typeid(double);
}

auto isCharacter(const std::any& value) -> bool {
  const std::type_info& type = value.type();
  return type == typeid(char);
}

auto isAlpha(char character) noexcept -> bool {
  return (character >= 'a' && character <= 'z') ||
         (character >= 'A' && character <= 'Z') || character == '_' ||
         character == ':';
}

auto isAlphaNumeric(char character) noexcept -> bool {
  return isAlpha(character) || isDigit(character);
}

auto isDigit(char character) noexcept -> bool {
  return character >= '0' && character <= '9';
}

auto validAssignment(const TokenType& tokenType) -> bool {
  return tokenType != TokenType::STRING_LITERAL;
}

auto checkOperands(const TokenType& left, const Token& token,
                   const TokenType& right) -> void {
  try {
    checkOperand(left);
    checkOperand(right);
  } catch (const RuntimeError& error) {
    throw RuntimeError(token, "Operands must be numbers.");
  } catch (const std::runtime_error& error) {
    throw RuntimeError(token, "Operands must be numbers.");
  }
}

auto checkOperand(const TokenType& tokenType) -> void {
  if (tokenType == TokenType::NUMBER ||
      tokenType == TokenType::DECIMAL_NUMBER ||
      tokenType == TokenType::CHARACTER_LITERAL) {
    return;
  }

  throw std::runtime_error("Operand must be a number.");
}

auto checkNumberOperand(const Token& token) -> void {
  if (token.literal.type() == typeid(int) ||
      token.literal.type() == typeid(double)) {
    return;
  }

  throw RuntimeError(token, "Operand must be a number.");
}

auto isTruthy(const std::any& value) -> bool {
  if (!value.has_value()) {
    return false;
  }
  if (value.type() == typeid(bool)) {
    return std::any_cast<bool>(value);
  }
  if (value.type() == typeid(double)) {
    return std::any_cast<double>(value) != 0;
  }
  if (value.type() == typeid(int)) {
    return std::any_cast<int>(value) != 0;
  }
  if (value.type() == typeid(char)) {
    return std::any_cast<char>(value) != '\0';
  }
  if (value.type() == typeid(std::string)) {
    return !std::any_cast<std::string>(value).empty();
  }

  return false;
}

auto isDataType(const TokenType& type) -> bool {
  return type == TokenType::INTEGER || type == TokenType::DECIMAL ||
         type == TokenType::CHAR || type == TokenType::BOOL;
}

auto isLiterals(const TokenType& type) -> bool {
  return type == TokenType::CHARACTER_LITERAL || type == TokenType::BOOL_TRUE ||
         type == TokenType::BOOL_FALSE || type == TokenType::NUMBER ||
         type == TokenType::DECIMAL_NUMBER;
}

auto typeEquality(VariableTokenType variableType, LiteralTokenType literalType)
    -> bool {
  switch (variableType.type) {
    case TokenType::INTEGER:
      return literalType.type == TokenType::NUMBER;
    case TokenType::DECIMAL:
      return literalType.type == TokenType::DECIMAL_NUMBER;
    case TokenType::BOOL:
      return literalType.type == TokenType::BOOL_TRUE ||
             literalType.type == TokenType::BOOL_FALSE;
    case TokenType::CHAR:
      return literalType.type == TokenType::CHARACTER_LITERAL;
    default:
      return false;
  }
}

auto typeToLiteralType(const TokenType& type) -> TokenType {
  switch (type) {
    case TokenType::INTEGER:
      return TokenType::NUMBER;
    case TokenType::DECIMAL:
      return TokenType::DECIMAL_NUMBER;
    case TokenType::BOOL:
      return TokenType::BOOL;
    case TokenType::CHAR:
      return TokenType::CHARACTER_LITERAL;
    default:
      return TokenType::NIL;
  }
}

auto doOperation(const char& left, TokenType operation, const char& right)
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
      return std::string(1, left).append(1, right);
    default:
      throw std::runtime_error("Invalid operation for char operands");
  }
}

void doOperation(TokenType& leftType, std::any& left, TokenType& rightType,
                 std::any& right, std::any& tempResult,
                 const TokenType& exprTokenType) {
  if (leftType == TokenType::NUMBER && rightType == TokenType::NUMBER) {
    tempResult = utility::doOperation(std::any_cast<int>(left), exprTokenType,
                                      std::any_cast<int>(right));
  } else if (leftType == TokenType::NUMBER &&
             rightType == TokenType::DECIMAL_NUMBER) {
    tempResult = utility::doOperation(std::any_cast<int>(left), exprTokenType,
                                      std::any_cast<double>(right));
  } else if (leftType == TokenType::DECIMAL_NUMBER &&
             rightType == TokenType::NUMBER) {
    tempResult = utility::doOperation(std::any_cast<double>(left),
                                      exprTokenType, std::any_cast<int>(right));
  } else if (leftType == TokenType::DECIMAL_NUMBER &&
             rightType == TokenType::DECIMAL_NUMBER) {
    tempResult =
        utility::doOperation(std::any_cast<double>(left), exprTokenType,
                             std::any_cast<double>(right));
  } else if (leftType == TokenType::CHARACTER_LITERAL &&
             rightType == TokenType::CHARACTER_LITERAL) {
    tempResult = utility::doOperation(std::any_cast<char>(left), exprTokenType,
                                      std::any_cast<char>(right));
  } else if (leftType == TokenType::CHARACTER_LITERAL &&
             rightType == TokenType::NUMBER) {
    tempResult = utility::doOperation(std::any_cast<char>(left), exprTokenType,
                                      std::any_cast<int>(right));
  } else if (leftType == TokenType::NUMBER &&
             rightType == TokenType::CHARACTER_LITERAL) {
    tempResult = utility::doOperation(std::any_cast<int>(left), exprTokenType,
                                      std::any_cast<char>(right));
  } else if (leftType == TokenType::CHARACTER_LITERAL &&
             rightType == TokenType::DECIMAL_NUMBER) {
    tempResult = utility::doOperation(std::any_cast<char>(left), exprTokenType,
                                      std::any_cast<double>(right));
  } else if (leftType == TokenType::DECIMAL_NUMBER &&
             rightType == TokenType::CHARACTER_LITERAL) {
    tempResult = utility::doOperation(
        std::any_cast<double>(left), exprTokenType, std::any_cast<char>(right));
  } else {
    throw std::runtime_error("Invalid operation");
  }
}

}  // namespace utility