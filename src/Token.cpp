#include "Token.hpp"

#include <ostream>

Token::Token(TokenType type, const std::string &lexeme, const std::any &literal,
			 int line)
	: type(type), lexeme(lexeme), literal(literal), line(line) {}

std::ostream &operator<<(std::ostream &os, const Token &t) {
	os << t.type << " " << t.lexeme << " ";
	return os;
}