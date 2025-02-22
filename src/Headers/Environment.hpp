#include <unordered_map>

#include "Token.hpp"

class Environment {
 public:
  auto defineVar(const std::string& name, const std::any& value, TokenType type)
      -> void;

  auto get(const Token& name) -> std::pair<std::any, TokenType>&;

 private:
  std::unordered_map<std::string, std::pair<std::any, TokenType>> values;
};