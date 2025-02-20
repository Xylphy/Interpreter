#pragma once

#include <stdexcept>

#include "Token.hpp"

class ParseError : public std::runtime_error {
 public:
  ParseError(const Token& token, const std::string& message);

 private:
};

class RuntimeError : public std::runtime_error {
 public:
  Token token;

  RuntimeError(Token token, const std::string& message);
};