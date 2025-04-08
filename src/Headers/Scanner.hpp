#pragma once

#include <unordered_map>
#include <vector>

#include "Token.hpp"

class Scanner {
 public:
  Scanner(std::string source);

  auto scanTokens() -> std::vector<Token>;

 private:
  void scanToken();
  void identifier();
  void number();
  void string();
  void charLiteral();
  void escapeChar();
  void addToken(TokenType type, const std::any& literal);
  void addToken(TokenType type);
  auto match(char&& expected) -> bool;
  auto isAtEnd() -> bool;
  auto peek() -> char;
  auto peekNext() -> char;
  auto advance() -> char;
  auto handleSingleCharacterToken(char character) -> void;
  auto handleMinus() -> void;
  auto handlePlus() -> void;
  auto handleEqual() -> void;
  auto handleLess() -> void;
  auto handleGreater() -> void;
  auto handleEscapeChar() -> void;
  auto handleNewLine() -> void;
  auto handleDefault(char character) -> void;

  size_t start = 0;
  size_t current = 0;
  size_t line = 1;

  std::string source;
  std::vector<Token> tokens;
  const std::unordered_map<std::string, TokenType> keywords = {
      {"UG", AND},           {"KLASE", CLASS},
      {"WALA", ELSE},        {"SA", FOR},
      {"BUHAT", FUN},        {"KUNG", IF},
      {"NULL", NIL},         {"O", OR},
      {"IPAKITA:", PRINT},   {"BALIK", RETURN},
      {"SUPER", SUPER},      {"KINI", THIS},
      {"MUGNA", VAR},        {"ALANG", WHILE},
      {"DAWAT:", INPUT},     {"SUGOD", START},
      {"KATAPUSAN", END},    {"NUMERO", INTEGER},
      {"TIPIK", DECIMAL},    {"TINUOD", BOOL},
      {"\"OO\"", BOOL_TRUE}, {"\"DILI\"", BOOL_FALSE},
      {"LETRA", CHAR},       {"PISI", STRING},
      {"\"WALA\"", NIL},     {"DILI", BANG},
      {"PUNDOK", BLOCK}};
};
