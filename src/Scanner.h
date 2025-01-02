#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <vector>

#include "Token.h"

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
	bool match(char expected);
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
		{"and", AND},	{"class", CLASS}, {"else", ELSE},	  {"false", FALSE},
		{"for", FOR},	{"fun", FUN},	  {"if", IF},		  {"nil", NIL},
		{"or", OR},		{"print", PRINT}, {"return", RETURN}, {"super", SUPER},
		{"this", THIS}, {"true", TRUE},	  {"var", VAR},		  {"while", WHILE},
	};
};
