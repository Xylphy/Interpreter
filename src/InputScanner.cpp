#include "Headers/InputScanner.hpp"

#include "Headers/Lib/utility.hpp"

InputScanner::InputScanner(std::string source, size_t line)
    : AbstractScanner(std::move(source), line) {}

auto InputScanner::scanToken() -> void {
  char character = advance();

  if (utility::isAlpha(character)) {
    
  }
}

void InputScanner::identifier() {
  while (utility::isAlphaNumeric(peek())) {
    advance();
  }

  addToken(IDENTIFIER);
}