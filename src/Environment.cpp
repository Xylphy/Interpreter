#include "Headers/Environment.hpp"

#include "Headers/Errors.hpp"
#include "Headers/Token.hpp"

auto Environment::defineVar(const std::string& name, const std::any& value,
                            TokenType type) -> void {
  values[name] = std::make_pair(value, type);
}

auto Environment::get(const Token& name) -> std::pair<std::any, TokenType>& {
  auto iterator = values.find(name.lexeme);

  if (iterator != values.end()) {
    return iterator->second;
  }

  throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
}