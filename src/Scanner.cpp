#include "Scanner.h"

#include "Token.h"
#include "cpplox.h"

Scanner::Scanner(const std::string &source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}

	tokens.emplace_back(END_OF_FILE, "", "", line);
	return tokens;
}

bool Scanner::isAtEnd() { return current >= source.length(); }

bool Scanner::match(char expected) {
	if (isAtEnd()) return false;
	if (source[current] != expected) return false;

	current++;
	return true;
}

void Scanner::scanToken() {
	char c = advance();
	switch (c) {
		case '(':
			addToken(LEFT_PAREN);
			break;
		case ')':
			addToken(RIGHT_PAREN);
			break;
		case '{':
			addToken(LEFT_BRACE);
			break;
		case '}':
			addToken(RIGHT_BRACE);
			break;
		case ',':
			addToken(COMMA);
			break;
		case '.':
			addToken(DOT);
			break;
		case '-':
			addToken(MINUS);
			break;
		case '+':
			addToken(PLUS);
			break;
		case ';':
			addToken(SEMICOLON);
			break;
		case '*':
			addToken(STAR);
			break;
		case '!':
			addToken(match('=') ? BANG_EQUAL : BANG);
			break;
		case '=':
			addToken(match('=') ? EQUAL_EQUAL : EQUAL);
			break;
		case '<':
			addToken(match('=') ? LESS_EQUAL : LESS);
			break;
		case '>':
			addToken(match('=') ? GREATER_EQUAL : GREATER);
			break;
		default:
			error(line, "Unexpected character.");
			break;
	}
}

char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type, std::string literal) {
	tokens.emplace_back(type, source.substr(start, current - start), literal,
						line);
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }
