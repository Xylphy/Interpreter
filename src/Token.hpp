#pragma once

#include <any>
#include <ostream>

enum TokenType {
	// Single-character tokens
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACE,
	RIGHT_BRACE,
	COMMA,
	DOT,
	MINUS,
	PLUS,
	SLASH,
	STAR,
	SEMICOLON,
	MODULO,
	NEW_LINE,
	CONCATENATOR,
	ESCAPE_CHARACTER,
	COLON,

	// One or two character tokens
	BANG,
	BANG_EQUAL,
	EQUAL,
	EQUAL_EQUAL,
	GREATER,
	GREATER_EQUAL,
	LESS,
	LESS_EQUAL,

	// Literals
	IDENTIFIER,
	CHARACTER,
	STRING,
	NUMBER,
	DECIMAL_NUMBER,
	BOOL_TRUE,
	BOOL_FALSE,
	CHARACTER_LITERAL,

	// Keywords
	AND,
	CLASS,
	ELSE,
	FALSE,
	FUN,
	FOR,
	IF,
	NIL,
	OR,
	PRINT,
	RETURN,
	SUPER,
	THIS,
	TRUE,
	VAR,
	WHILE,
	INPUT,
	START,
	END,
	INTEGER,
	DECIMAL,
	BOOL,
	CHAR,

	END_OF_FILE
};

class Token {
   public:
	Token(TokenType type, const std::string &lexeme, const std::any &literal,
		  int line);
	friend std::ostream &operator<<(std::ostream &os, const Token &t);

   private:
	TokenType type;
	std::string lexeme;
	std::any literal;
	int line;
};

std::ostream &operator<<(std::ostream &os, const Token &t);