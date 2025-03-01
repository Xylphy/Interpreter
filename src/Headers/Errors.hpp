#pragma once

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

class BreakError : public std::runtime_error {
 public:
  BreakError();
};

class SyntaxError : public std::runtime_error {
 public:
 Token token;
  SyntaxError(Token token, const std::string& message);
};