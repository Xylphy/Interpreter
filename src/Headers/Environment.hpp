#include <any>
#include <memory>
#include <unordered_map>

#include "Token.hpp"

class Environment {
 public:
  Environment();
  Environment(std::shared_ptr<Environment> enclosing);

  auto defineVar(const Token& token, const std::any& value, TokenType type)
      -> void;

  auto get(const Token& name) -> std::pair<std::any, TokenType>;
  auto assign(const Token& token, const std::any& value, TokenType type)
      -> void;

 private:
  std::unordered_map<std::string, std::pair<std::any, TokenType>> variables;
  std::shared_ptr<Environment> enclosing;
};