#include "Headers/Interpreter.hpp"

#include <print>

#include "Headers/Errors.hpp"
#include "Headers/Lib/utility.hpp"
#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

Interpreter::Interpreter() : environment(new Environment()) {}

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
    case TokenType::CHARACTER_LITERAL:
      toSet = toGet;
      break;
    default:
      result = toSet;
  }
}

auto Interpreter::setInterpretResult(Expr* expr) -> void {
  expr->accept(*this);
}

auto Interpreter::setInterpretResult(const std::vector<Stmt*>& statements)
    -> void {
  try {
    for (Stmt* statement : statements) {
      std::print("Executing statement\n");
      execute(statement);
    }
  } catch (const RuntimeError& error) {
    BisayaPP::runtimeError(error);
  }
}

auto Interpreter::execute(Stmt* statement) -> void { statement->accept(*this); }

auto Interpreter::evaluate(Expr* expression) -> bool {
  try {
    setPrintResult(expression);
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
    } else if (tempResult.type() == typeid(double)) {
      type = TokenType::DECIMAL_NUMBER;
    } else if (tempResult.type() == typeid(bool)) {
      if (std::any_cast<bool>(tempResult)) {
        type = TokenType::BOOL_TRUE;
      } else {
        type = TokenType::BOOL_FALSE;
      }
    } else {
      type = TokenType::STRING_LITERAL;
    }

  } catch (const RuntimeError& error) {
    if (Expr.op.type == TokenType::CONCATENATOR) {
      type = TokenType::STRING_LITERAL;

      tempResult =
          utility::anyToString(left).append(utility::anyToString(right));
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

auto Interpreter::visitExpressionStmt(const Expression& Stmt) -> void {
  evaluate(Stmt.expression);
}

auto Interpreter::visitPrintStmt(const Print& Stmt) -> void {
  bool success = evaluate(Stmt.expression);
  if (success) {
    std::print("{}\n", utility::anyToString(result));
  }
}

auto Interpreter::visitVarStmt(const Var& Stmt) -> void {
  std::any value;
  TokenType tokenType = TokenType::UNITIALIZED;

  if (Stmt.initializer != nullptr) {
    setInterpretResult(Stmt.initializer);
    value = result;
    tokenType = type;
    utility::convertData(tokenType, value);
  }

  if (!utility::validAssignment(Stmt.name.type)) {
    throw RuntimeError(Stmt.name, "Invalid assignment target.");
  }

  environment->defineVar(Stmt.name.lexeme, value, tokenType);
}

auto Interpreter::visitVariableExpr(const Variable& Expr) -> void {
  std::pair<std::any, TokenType>& variableExpr = environment->get(Expr.name);

  type = variableExpr.second;

  if (type == TokenType::UNITIALIZED) {
    throw RuntimeError(Expr.name, "Variable not initialized.");
  }

  setResult(result, variableExpr.first, type);
}

auto Interpreter::visitAssignExpr(const Assign& Expr) -> void {
  setInterpretResult(Expr.value);
  utility::convertData(type, result);
  environment->assign(Expr.name, result, type);
}

auto Interpreter::visitBlockStmt(const Block& Stmt) -> void {
  executeBlock(Stmt.statements, new Environment(environment));
}

auto Interpreter::executeBlock(const std::vector<Stmt*>& statements,
                               Environment* env) -> void {
  Environment* previous = environment;
  environment = env;
  for (Stmt* statement : statements) {
    execute(statement);
  }
  environment = previous;
}

auto Interpreter::visitIfStmt(const If& Stmt) -> void {
  evaluate(Stmt.condition);

  if (isTruthy(result, type)) {
    execute(Stmt.thenBranch);
  } else if (Stmt.elseBranch != nullptr) {
    execute(Stmt.elseBranch);
  }
}

auto Interpreter::visitWhileStmt(const While& Stmt) -> void {
  evaluate(Stmt.condition);

  try {
    while (isTruthy(result, type)) {
      execute(Stmt.body);
      evaluate(Stmt.condition);
    }
  } catch (const BreakError& error) {
    return;
  }
}

auto Interpreter::visitLogicalExpr(const Logical& Expr) -> void {
  evaluate(Expr.left);

  if (Expr.op.type == TokenType::OR) {
    if (isTruthy(result, type)) {
      return;
    }
  } else {
    if (!isTruthy(result, type)) {
      return;
    }
  }

  evaluate(Expr.right);
}