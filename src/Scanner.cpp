#include "Headers/Scanner.hpp"

#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

Scanner::Scanner(std::string source) : source(std::move(source)) {}

auto Scanner::scanTokens() -> std::vector<Token> {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.emplace_back(END_OF_FILE, "", "", line);
  return tokens;
}

auto Scanner::isAtEnd() -> bool { return current >= source.length(); }

auto Scanner::match(char&& expected) -> bool {
  if (isAtEnd()) {
    return false;
  }
  if (source[current] != expected) {
    return false;
  }

  current++;
  return true;
}

auto Scanner::peek() -> char {
  if (isAtEnd()) {
    return '\0';
  }
  return source[current];
}

auto Scanner::peekNext() -> char {
  if (current + 1 >= source.length()) {
    return '\0';
  }

  return source[current + 1];
}

void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') {
      line++;
    }

    advance();
  }

  if (isAtEnd()) {
    BisayaPP::error(line, "Unterminated string.");
    return;
  }
  advance();

  std::string value = source.substr(start, current - start);

  auto iterator = keywords.find(value);
  if (iterator != keywords.end()) {
    addToken(iterator->second);
  } else {
    addToken(STRING_LITERAL, value.substr(1, value.length() - 2));
  }
}

void Scanner::charLiteral() {
  while (peek() != '\'' && !isAtEnd()) {
    if (peek() == '\n') {
      line++;
    }

    advance();
  }

  if (isAtEnd()) {
    BisayaPP::error(line, "Unterminated character literal.");
    return;
  }
  advance();

  addToken(CHARACTER_LITERAL, source.substr(start + 1, current - start - 2));
}

auto Scanner::isDigit(char character) -> bool {
  return character >= '0' && character <= '9';
}

void Scanner::number() {
  while (isDigit(peek())) {
    advance();
  }

  bool isDecimal = false;

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    isDecimal = true;

    while (isDigit(peek())) {
      advance();
    }
  }

  if (isDecimal) {
    addToken(DECIMAL_NUMBER, std::stod(source.substr(start, current - start)));
  } else {
    addToken(NUMBER, std::stoi(source.substr(start, current - start)));
  }
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek())) {
    advance();
  }

  auto iterator = keywords.find(source.substr(start, current - start));

  addToken(iterator != keywords.end() ? iterator->second : IDENTIFIER);
}

auto Scanner::isAlpha(char character) -> bool {
  return (character >= 'a' && character <= 'z') ||
         (character >= 'A' && character <= 'Z') || character == '_' || character == ':';
}

auto Scanner::isAlphaNumeric(char character) -> bool {
  return isAlpha(character) || isDigit(character);
}

void Scanner::escapeChar() {
  addToken(ESCAPE_CHARACTER, source.substr(start, current - start));
  current += 2;
}

void Scanner::scanToken() {
  char character = advance();

  switch (character) {
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
      if (match('-')) {
        while (peek() != '\n' && !isAtEnd()) {
          advance();
        }
      } else {
        addToken(MINUS);
      }
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
      if (isDigit(character)) {
        number();
      } else if (isAlpha(character)) {
        identifier();
      } else {
        BisayaPP::error(line,
                        "Unexpected character: " + std::to_string(character));
      }
      break;
  }
}

auto Scanner::advance() -> char { return source[current++]; }

void Scanner::addToken(TokenType type, const std::any& literal) {
  tokens.emplace_back(type, source.substr(start, current - start), literal,
                      line);
}

void Scanner::addToken(TokenType type) { addToken(type, ""); }
