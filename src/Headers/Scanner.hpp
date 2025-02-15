#pragma once

#include <any>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

#include "Token.hpp"

class Scanner {
   public:
    Scanner(const std::string& source);

    std::vector<Token> scanTokens();

   private:
    void scanToken();
    void identifier();
    void number();
    void string();
    void charLiteral();
    void escapeChar();
    void addToken(TokenType type, std::any literal);
    void addToken(TokenType type);
    bool match(char&& expected);
    bool isAtEnd();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    bool isDigit(char c);
    char peek();
    char peekNext();
    char advance();

    size_t                                           start   = 0;
    size_t                                           current = 0;
    size_t                                           line    = 1;
    std::string                                      source;
    std::vector<Token>                               tokens;
    const std::unordered_map<std::string, TokenType> keywords = {
      {"UG", AND},           {"KLASE", CLASS},
      {"WALA", ELSE},        {"SA", FOR},
      {"BUHAT", FUN},        {"KUNG", IF},
      {"NULL", NIL},         {"O", OR},
      {"IPAKITA", PRINT},    {"BALIK", RETURN},
      {"SUPER", SUPER},      {"KINI", THIS},
      {"MUGNA", VAR},        {"ALANG", WHILE},
      {"DAWAT", INPUT},      {"SUGOD", START},
      {"KATAPUSAN", END},    {"NUMERO", INTEGER},
      {"PITIK", DECIMAL},    {"TINUOD", BOOL},
      {"\"OO\"", BOOL_TRUE}, {"\"DILI\"", BOOL_FALSE},
      {"LETRA", CHAR},       {"PISI", STRING}};
};
