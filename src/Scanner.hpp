#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <vector>

#include "Token.hpp"

class Scanner {
   public:
	Scanner(const std::string &source);

	std::vector<Token> scanTokens();

   private:
	bool isAtEnd();
	void scanToken();
	void identifier();
	void number();
	void string();
	void charLiteral();
	void escapeChar();
	bool match(char &&expected);
	char peek();
	char peekNext();
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);
	bool isDigit(char c);
	char advance();
	void addToken(TokenType type, std::any literal);
	void addToken(TokenType type);

	int start = 0;
	int current = 0;
	int line = 1;
	std::string source;
	std::vector<Token> tokens;
	const std::unordered_map<std::string, TokenType> keywords = {
		{"UG", AND},		  {"KLASE", CLASS},	  {"KUNG WALA", ELSE},
		{"ALANG SA", FOR},	  {"BUHAT", FUN},	  {"KUNG", IF},
		{"NULL", NIL},		  {"O", OR},		  {"IPAKITA", PRINT},
		{"BALIK", RETURN},	  {"SUPER", SUPER},	  {"KINI", THIS},
		{"MUGNA", VAR},		  {"SAMTANG", WHILE}, {"DAWAT", INPUT},
		{"SUGOD", START},	  {"KATAPUSAN", END}, {"NUMERO", INTEGER},
		{"PITIK", DECIMAL},	  {"TINUOD", BOOL},	  {"OO", BOOL_TRUE},
		{"DILI", BOOL_FALSE}, {"LETRA", CHAR},
	};
};
