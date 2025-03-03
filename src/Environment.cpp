#include "Headers/Environment.hpp"

#include "Headers/Errors.hpp"
#include "Headers/Lib/utility.hpp"

Environment::Environment() : enclosing(nullptr) {}

Environment::Environment(Environment* enclosing) : enclosing(enclosing) {}

auto Environment::defineVar(const std::string& name, const std::any& value,
                            TokenType type) -> void {
                              
  values[name] = std::make_pair(value, type);
}

auto Environment::get(const Token& name) -> std::pair<std::any, TokenType>& {
  auto iterator = values.find(name.lexeme);

  if (iterator != values.end()) {
    return iterator->second;
  }

  if (enclosing != nullptr) {
    return enclosing->get(name);
  }

  throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}

auto Environment::assign(const Token& name, const std::any& value,
                         TokenType type) -> void {
  if (values.find(name.lexeme) != values.end()) {
    values[name.lexeme] = std::make_pair(value, type);
    return;
  }

  if (enclosing != nullptr) {
    enclosing->assign(name, value, type);
    return;
  }

  throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}