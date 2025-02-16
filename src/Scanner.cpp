#include "Headers/Scanner.hpp"

#include <any>
#include <string>
#include <unordered_map>

#include "Headers/Token.hpp"
#include "Headers/interpreter.hpp"

Scanner::Scanner(const std::string& source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(END_OF_FILE, "", "", line);
  return tokens;
}

bool Scanner::isAtEnd() { return current >= source.length(); }

bool Scanner::match(char&& expected) {
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
    BisayaPP::error(line, "Unterminated string.");
    return;
  }
  advance();

  std::string value = source.substr(start, current - start);

  std::unordered_map<std::string, TokenType>::const_iterator it =
      keywords.find(value);
  if (it != keywords.end())
    addToken(it->second);
  else
    addToken(STRING_LITERAL, value.substr(1, value.length() - 2));
}

void Scanner::charLiteral() {
  while (peek() != '\'' && !isAtEnd()) {
    if (peek() == '\n') line++;

    advance();
  }

  if (isAtEnd()) {
    BisayaPP::error(line, "Unterminated character literal.");
    return;
  }
  advance();

  addToken(CHARACTER_LITERAL, source.substr(start + 1, current - start - 2));
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

void Scanner::number() {
  while (isDigit(peek())) advance();

  bool isDecimal = false;

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    isDecimal = true;

    while (isDigit(peek())) advance();
  }

  if (isDecimal)
    addToken(DECIMAL, std::stod(source.substr(start, current - start)));
  else
    addToken(NUMBER, std::stoi(source.substr(start, current - start)));
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek())) advance();

  typename std::unordered_map<std::string, TokenType>::const_iterator it =
      keywords.find(source.substr(start, current - start));

  addToken(it != keywords.end() ? it->second : IDENTIFIER);
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

void Scanner::escapeChar() {
  addToken(ESCAPE_CHARACTER, source.substr(start, current - start));
  current += 2;
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
      /* 		case '.':
                          addToken(DOT);
                          break; */
    case '-':
      if (match('-'))
        while (peek() != '\n' && !isAtEnd()) advance();
      else if (match(isDigit(peek())))
        number();
      else
        addToken(MINUS);
      break;
    case ':':
      addToken(COLON);
      break;
    case '+':
      addToken(PLUS);
      break;
      /* 		case ';':
                          addToken(SEMICOLON);  // Optional
                          break; */
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
      addToken(SLASH);
      break;
    case '%':
      addToken(MODULO);
      break;
    case '&':
      addToken(CONCATENATOR);
      break;
    case '$':
      addToken(NEW_LINE);
      break;
    case '[':
      if (peekNext() == ']') {
        escapeChar();
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      break;
    case '\n':
      line++;
      addToken(SEMICOLON);
      break;
    case '"':
      string();
      break;
    case '\'':
      charLiteral();
      break;
    default:
      if (isDigit(c))
        number();
      else if (isAlpha(c))
        identifier();
      else
        BisayaPP::error(line, "Unexpected character: " + std::to_string(c));

      break;
  }
}

char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type, std::any literal) {
  tokens.emplace_back(type, source.substr(start, current - start), literal,
                      line);
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }
