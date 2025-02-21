#include "Headers/Interpreter.hpp"

#include <any>
#include <cmath>
#include <print>
#include <stdexcept>

#include "Headers/Errors.hpp"
#include "Headers/Lib/utility.hpp"
#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

auto Interpreter::checkNumberOperands(const Token& token, TokenType left,
                                      TokenType right) -> void {
  try {
    checkNumberOperand(token, left);
    checkNumberOperand(token, right);
  } catch (const RuntimeError& error) {
    throw RuntimeError(token, "Operands must be numbers.");
  }
}

auto Interpreter::setResult(std::any& toSet, const std::any& toGet,
                            TokenType type) -> void {
  switch (type) {
    case TokenType::NUMBER:
    case TokenType::DECIMAL_NUMBER:
    case TokenType::STRING_LITERAL:
    case TokenType::CHAR:
    case TokenType::BOOL_TRUE:
    case TokenType::BOOL_FALSE:
      toSet = toGet;
      break;
    default:
      result = toSet;
  }
}

auto Interpreter::setInterpretResult(Expr* expr) -> void {
  expr->accept(*this);
}

auto Interpreter::evaluate(Expr* expression) -> bool {
  try {
    setPrintResult(expression);
    std::string resultString;
    utility::anyToString(resultString, result);
    std::print("Result is: {}\n", resultString);
    return true;
  } catch (RuntimeError& error) {
    BisayaPP::runtimeError(error);
    return false;
  }
}

auto Interpreter::visitBinaryExpr(const Binary& Expr) -> void {
  setInterpretResult(Expr.left);
  TokenType leftType = type;
  std::any left;
  setResult(left, result, leftType);

  setInterpretResult(Expr.right);
  TokenType rightType = type;
  std::any right;
  setResult(right, result, rightType);

  std::string leftConvert;
  std::string rightConvert;
  utility::anyToString(leftConvert, left);
  utility::anyToString(rightConvert, right);

  if (!utility::checkValidOperation(left, Expr.op.type, right)) {
    throw RuntimeError(Expr.op, "Invalid operation");
  }

  std::any tempResult;

  try {
    checkNumberOperands(Expr.op, leftType,
                        rightType);  // throws RuntimeError if not numbers
    const TokenType& exprTokenType = Expr.op.type;

    if (leftType == TokenType::NUMBER && rightType == TokenType::NUMBER) {
      tempResult = numericOperation(std::any_cast<int>(left), exprTokenType,
                                    std::any_cast<int>(right));
    } else if (leftType == TokenType::NUMBER &&
               rightType == TokenType::DECIMAL_NUMBER) {
      tempResult = numericOperation(std::any_cast<int>(left), exprTokenType,
                                    std::any_cast<double>(right));
    } else if (leftType == TokenType::DECIMAL_NUMBER &&
               rightType == TokenType::NUMBER) {
      tempResult = numericOperation(std::any_cast<double>(left), exprTokenType,
                                    std::any_cast<int>(right));
    } else if (leftType == TokenType::DECIMAL_NUMBER &&
               rightType == TokenType::DECIMAL_NUMBER) {
      tempResult = numericOperation(std::any_cast<double>(left), exprTokenType,
                                    std::any_cast<double>(right));
    }

    if (tempResult.type() == typeid(int)) {
      type = TokenType::NUMBER;
    } else if (result.type() == typeid(double)) {
      type = TokenType::DECIMAL_NUMBER;
    } else {
      type = TokenType::STRING_LITERAL;
    }

  } catch (const RuntimeError& error) {
    if (Expr.op.type == TokenType::CONCATENATOR) {
      type = TokenType::STRING_LITERAL;

      std::string leftString;
      std::string rightString;
      utility::anyToString(leftString, left);
      utility::anyToString(rightString, right);

      tempResult = leftString.append(rightString);
    }
  } catch (const std::runtime_error& error) {  // Division by zero
    throw RuntimeError(Expr.op, error.what());
  }

  setResult(result, tempResult, type);
}

auto Interpreter::visitGroupingExpr(const Grouping& Expr) -> void {
  setInterpretResult(Expr.expression);
}

auto Interpreter::visitLiteralExpr(const Literal& Expr) -> void {
  type = Expr.type;
  std::any value = Expr.value;
  setResult(result, value, type);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"

auto Interpreter::visitUnaryExpr(const Unary& Expr) -> void {
  setInterpretResult(Expr.right);
  TokenType rightType = type;

  bool newResult;
  std::any tempResult;
  std::any right;
  setResult(right, result, rightType);
  switch (Expr.op.type) {
    case TokenType::BANG:
      newResult = isTruthy(right, rightType);
      type = newResult ? TokenType::BOOL_TRUE : TokenType::BOOL_FALSE;
      setResult(result, newResult, type);
      break;
    case TokenType::MINUS:
      checkNumberOperand(Expr.op, rightType);
      type = TokenType::NUMBER;
      setResult(result, right, rightType);
      break;
  }
}

#pragma clang diagnostic pop

auto Interpreter::setPrintResult(Expr* expr) -> void { expr->accept(*this); }

auto Interpreter::isTruthy(const std::any& value, TokenType type) -> bool {
  if (type == TokenType::NIL) {
    return false;
  }
  if (type == TokenType::BOOL_TRUE) {
    return true;
  }
  if (type == TokenType::DECIMAL_NUMBER) {
    return std::any_cast<double>(value) != 0;
  }
  if (type == TokenType::NUMBER) {
    return std::any_cast<int>(value) != 0;
  }
  if (type == TokenType::STRING_LITERAL) {
    return !std::any_cast<std::string>(value).empty();
  }

  return false;
}

auto Interpreter::checkNumberOperand(const Token& token, TokenType operand)
    -> void {
  if (operand == TokenType::NUMBER || operand == TokenType::DECIMAL_NUMBER) {
    return;
  }
  throw RuntimeError(token, "Operand must be a number.");
}