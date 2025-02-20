#include "Headers/Interpreter.hpp"

#include <print>

#include "Headers/Errors.hpp"
#include "Headers/Lib/utility.hpp"
#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

auto Interpreter::checkNumberOperands(const Token& token, TokenType left,
                                      TokenType right) -> void {
  if (left == TokenType::NUMBER && right == TokenType::NUMBER) {
    return;
  }
  throw RuntimeError(token, "Operands must be numbers.");
}

auto Interpreter::setResult(std::any& toSet, const std::any& toGet,
                            TokenType type) -> void {
  switch (type) {
    case TokenType::NUMBER:
    case TokenType::STRING:
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch"

auto Interpreter::visitBinaryExpr(const Binary& Expr) -> void {
  setInterpretResult(Expr.left);
  TokenType leftType = type;
  std::any left;
  setResult(left, result, leftType);

  setInterpretResult(Expr.right);
  TokenType rightType = type;
  std::any right;
  setResult(right, result, rightType);

  bool newResult;
  std::any tempResult;

  auto leftNum = std::any_cast<double>(left);
  auto rightNum = std::any_cast<double>(right);
  std::string leftStr;
  std::string rightStr;
  switch (Expr.op.type) {
    case TokenType::GREATER:
      checkNumberOperands(Expr.op, leftType, rightType);
      newResult = leftNum > rightNum;
      break;
    case TokenType::GREATER_EQUAL:
      checkNumberOperands(Expr.op, leftType, rightType);
      newResult = leftNum >= rightNum;
      break;
    case TokenType::LESS:
      checkNumberOperands(Expr.op, leftType, rightType);
      newResult = leftNum < rightNum;
      break;
    case TokenType::LESS_EQUAL:
      checkNumberOperands(Expr.op, leftType, rightType);
      newResult = leftNum <= rightNum;
      break;
    case TokenType::BANG_EQUAL:
      checkNumberOperands(Expr.op, leftType, rightType);
      newResult = leftNum != rightNum;
      break;
    case TokenType::EQUAL_EQUAL:
      checkNumberOperands(Expr.op, leftType, rightType);
      newResult = leftNum == rightNum;
      break;
    case TokenType::MINUS:
      checkNumberOperands(Expr.op, leftType, rightType);
      tempResult = leftNum - rightNum;
      goto SET_NUMBER;
    case TokenType::PLUS:
      checkNumberOperands(Expr.op, leftType, rightType);
      tempResult = leftNum + rightNum;
      goto SET_NUMBER;
    case TokenType::SLASH:
      checkNumberOperands(Expr.op, leftType, rightType);
      tempResult = leftNum / rightNum;
      goto SET_NUMBER;
    case TokenType::STAR:
      checkNumberOperands(Expr.op, leftType, rightType);
      tempResult = leftNum * rightNum;
      goto SET_NUMBER;
    case TokenType::CONCATENATOR:
      utility::anyToString(leftStr, left);
      utility::anyToString(rightStr, right);
      tempResult = leftStr.append(rightStr);
      goto SET_RESULT;
  }
  type = newResult ? TokenType::BOOL_TRUE : TokenType::BOOL_FALSE;
  tempResult = (newResult);

SET_NUMBER:
  type = TokenType::NUMBER;

SET_RESULT:
  setResult(result, tempResult, type);
}

#pragma clang diagnostic pop

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
    // negate
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
  if (type == TokenType::NUMBER) {
    return std::any_cast<double>(value) != 0;
  }
  if (type == TokenType::STRING_LITERAL) {
    return !std::any_cast<std::string>(value).empty();
  }

  return false;
}

auto Interpreter::checkNumberOperand(const Token& token, TokenType operand)
    -> void {
  if (operand == TokenType::NUMBER) {
    return;
  }
  throw RuntimeError(token, "Operand must be a number.");
}