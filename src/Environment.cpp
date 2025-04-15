#include "Headers/Environment.hpp"

#include <memory>

#include "Headers/Errors.hpp"
#include "Headers/Lib/utility.hpp"
#include "Headers/Token.hpp"

Environment::Environment() : enclosing(nullptr) {}

Environment::Environment(std::shared_ptr<Environment> enclosing)
    : enclosing(std::move(enclosing)) {}

auto Environment::defineVar(const Token& token, const std::any& value,
                            TokenType type) -> void {
  if (!utility::typeEquality({token.type}, {type}) &&
      type != TokenType::UNITIALIZED && token.type != TokenType::UNITIALIZED) {
    throw RuntimeError(token, "Invalid assignment target.");
  }
  /*
  Unitialized means the data type has been resetted and it assumes the variable was already declared
  */
  if (token.type == TokenType::UNITIALIZED) { 
    variables[token.lexeme].first = value;
  } else {
    variables[token.lexeme] = std::make_pair(value, token.type);
  }
}

auto Environment::get(const Token& name) -> std::pair<std::any, TokenType> {
  if (auto iterator = variables.find(name.lexeme);
      iterator != variables.end()) {
    std::pair<std::any, TokenType> value = iterator->second;
    value.second = utility::typeToLiteralType(value.second);

    if (value.second == TokenType::BOOL) {
      value.second = std::any_cast<bool>(value.first) ? TokenType::BOOL_TRUE
                                                      : TokenType::BOOL_FALSE;
    }
    return value;
  }

  if (enclosing != nullptr) {
    return enclosing->get(name);
  }

  throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

auto Environment::assign(const Token& token, const std::any& value,
                         TokenType type) -> void {
  if (auto iterator = variables.find(token.lexeme);
      iterator != variables.end()) {
    if (!utility::typeEquality({iterator->second.second}, {type}) &&
        type != TokenType::UNITIALIZED &&
        token.type != TokenType::UNITIALIZED) {
      throw RuntimeError(token, "Invalid assignment target.");
    }
    variables[token.lexeme].first = value;
    return;
  }

  if (enclosing != nullptr) {
    enclosing->assign(token, value, type);
    return;
  }

  throw RuntimeError(token, "Undefined variable '" + token.lexeme + "'.");
}