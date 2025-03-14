#include <any>
#include <unordered_map>

#include "Token.hpp"

class Environment {
 public:
  Environment();
  Environment(Environment* enclosing);

  auto defineVar(const std::string& name, const std::any& value, TokenType type)
      -> void;

  auto get(const Token& name) -> std::pair<std::any, TokenType>&;
  auto assign(const Token& name, const std::any& value, TokenType type) -> void;

  ~Environment() = default;

 private:
  std::unordered_map<std::string, std::pair<std::any, TokenType>> values;
  Environment* enclosing;
};