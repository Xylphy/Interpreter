#include "Headers/Interpreter.hpp"

#include <iostream>
#include <memory>

#include "Headers/Lib/utility.hpp"
#include "Headers/bisayaPP.hpp"

Interpreter::Interpreter() : environment(std::make_shared<Environment>()) {}

auto Interpreter::setResult(std::any& toSet, const std::any& toGet,
                            TokenType tokenType) -> void {
  switch (tokenType) {
    case TokenType::NUMBER:
    case TokenType::DECIMAL_NUMBER:
    case TokenType::STRING_LITERAL:
    case TokenType::BOOL_TRUE:
    case TokenType::BOOL_FALSE:
    case TokenType::CHARACTER_LITERAL:
      toSet = toGet;
      break;
    default:
      result = toSet;
  }
}

auto Interpreter::setInterpretResult(const std::unique_ptr<Expr>& expr)
    -> void {
  expr->accept(*this);
}

auto Interpreter::setInterpretResult(
    const std::vector<std::unique_ptr<Stmt>>& statements) -> void {
  try {
    for (const std::unique_ptr<Stmt>& statement : statements) {
      execute(statement);
    }
  } catch (const RuntimeError& error) {
    BisayaPP::runtimeError(error);
  }
}

auto Interpreter::execute(const std::unique_ptr<Stmt>& statement) -> void {
  statement->accept(*this);
}

auto Interpreter::evaluate(const std::unique_ptr<Expr>& expression) -> bool {
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
    utility::checkNumberOperands(
        leftType, Expr.op,
        rightType);  // throws RuntimeError if not numbers
    const TokenType& exprTokenType = Expr.op.type;

    if (leftType == TokenType::NUMBER && rightType == TokenType::NUMBER) {
      tempResult = utility::numericOperation(
          std::any_cast<int>(left), exprTokenType, std::any_cast<int>(right));
    } else if (leftType == TokenType::NUMBER &&
               rightType == TokenType::DECIMAL_NUMBER) {
      tempResult =
          utility::numericOperation(std::any_cast<int>(left), exprTokenType,
                                    std::any_cast<double>(right));
    } else if (leftType == TokenType::DECIMAL_NUMBER &&
               rightType == TokenType::NUMBER) {
      tempResult =
          utility::numericOperation(std::any_cast<double>(left), exprTokenType,
                                    std::any_cast<int>(right));
    } else if (leftType == TokenType::DECIMAL_NUMBER &&
               rightType == TokenType::DECIMAL_NUMBER) {
      tempResult =
          utility::numericOperation(std::any_cast<double>(left), exprTokenType,
                                    std::any_cast<double>(right));
    }

    if (tempResult.type() == typeid(int)) {
      type = TokenType::NUMBER;
    } else if (tempResult.type() == typeid(double)) {
      type = TokenType::DECIMAL_NUMBER;
    } else if (tempResult.type() == typeid(bool)) {
      type = std::any_cast<bool>(tempResult) ? TokenType::BOOL_TRUE
                                             : TokenType::BOOL_FALSE;
    } else {
      type = TokenType::STRING_LITERAL;
    }

  } catch (const RuntimeError& error) {
    TokenType tokenType = Expr.op.type;
    type = TokenType::STRING_LITERAL;
    if (tokenType == TokenType::CONCATENATOR) {
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

auto Interpreter::visitUnaryExpr(const Unary& Expr) -> void {
  setInterpretResult(Expr.right);
  TokenType rightType = type;

  bool newResult;
  std::any tempResult;
  std::any right;
  setResult(right, result, rightType);

  switch (Expr.op.type) {
    case TokenType::BANG:
      newResult = utility::isTruthy(right);
      type = newResult ? TokenType::BOOL_TRUE : TokenType::BOOL_FALSE;
      setResult(result, newResult, type);
      break;
    case TokenType::MINUS:
      utility::checkNumberOperand(Expr.op.type);
      type = TokenType::NUMBER;
      setResult(result, right, rightType);
      break;
    default:;
  }
}

auto Interpreter::setPrintResult(const std::unique_ptr<Expr>& expr) -> void {
  expr->accept(*this);
}

auto Interpreter::visitExpressionStmt(const Expression& Stmt) -> void {
  evaluate(Stmt.expression);
}

auto Interpreter::visitPrintStmt(const Print& Stmt) -> void {
  if (evaluate(Stmt.expression)) {
    std::cout << utility::anyToString(result);
  }
}

auto Interpreter::visitInputStmt(const Input& stmt) -> void {
  const size_t size = stmt.inputs.size();

  for (size_t i = 0; i < size; i++) {
    environment->assign(stmt.variables[i], stmt.inputs[i].literal,
                        stmt.inputs[i].type);
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
  executeBlock(Stmt.statements, std::make_shared<Environment>(environment));
}

auto Interpreter::executeBlock(
    const std::vector<std::unique_ptr<Stmt>>& statements,
    std::shared_ptr<Environment>&& env) -> void {
  std::shared_ptr<Environment> previous = std::move(environment);
  environment = env;

  for (const std::unique_ptr<Stmt>& statement : statements) {
    execute(statement);
  }

  environment = std::move(previous);
}

auto Interpreter::visitIfStmt(const If& Stmt) -> void {
  evaluate(Stmt.condition);

  if (utility::isTruthy(result)) {
    execute(Stmt.thenBranch);
  } else if (Stmt.elseBranch != nullptr) {
    execute(Stmt.elseBranch);
  }
}

auto Interpreter::visitWhileStmt(const While& Stmt) -> void {
  evaluate(Stmt.condition);

  try {
    while (utility::isTruthy(result)) {
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
    if (utility::isTruthy(result)) {
      return;
    }
  } else {
    if (!utility::isTruthy(result)) {
      return;
    }
  }

  evaluate(Expr.right);
}