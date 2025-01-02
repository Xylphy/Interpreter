#include "Scanner.h"

#include <any>
#include <string>

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

char Scanner::peek() {
	if (isAtEnd()) return '\0';
	return source[current];
}

char Scanner::peekNext() {
	if (current + 1 >= source.length()) return '\0';

	return source[current + 1];
}

void Scanner::string() {
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') line++;

		advance();
	}

	if (isAtEnd()) {
		error(line, "Unterminated string.");
		return;
	}

	advance();
	addToken(STRING, source.substr(start + 1, start - current - 1));
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

void Scanner::number() {
	while (isDigit(peek())) advance();

	if (peek() == '.' && isDigit(peekNext())) {
		advance();

		while (isDigit(peek())) advance();
	}

	addToken(NUMBER, std::stod(source.substr(start, current - start)));
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
		case '/':
			if (match('/')) {
				while (peek() != '\n' && !isAtEnd()) advance();
			} else {
				addToken(SLASH);
			}
			break;
		case ' ':
		case '\r':
		case '\t':
			break;
		case '\n':
			line++;
			break;
		case '"':
			string();
			break;
		default:
			if (isDigit(c)) {
				number();
			} else {
				error(line, "Unexpected character.");
			}
			break;
	}
}

char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type, std::any literal) {
	tokens.emplace_back(type, source.substr(start, current - start), literal,
						line);
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }
