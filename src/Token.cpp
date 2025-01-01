#include "Token.h"

#include <ostream>

Token::Token(TokenType type, const std::string &lexeme,
			 const std::string &literal, int line)
	: type(type), lexeme(lexeme), literal(literal), line(line) {}

std::ostream &operator<<(std::ostream &os, const Token &t) {
	os << t.type << " " << t.lexeme << " " << t.literal;
	return os;
}