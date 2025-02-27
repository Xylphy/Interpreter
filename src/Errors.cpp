#include "Headers/Errors.hpp"

#include <stdexcept>

#include "Headers/Token.hpp"
#include "Headers/bisayaPP.hpp"

ParseError::ParseError(const Token& token, const std::string& message)
    : std::runtime_error(message) {
  // BisayaPP::error(token, message);
}

RuntimeError::RuntimeError(Token token, const std::string& message)
    : token(std::move(token)), std::runtime_error(message) {}

BreakError::BreakError() : std::runtime_error("Using exception to break out of a loop.") {}