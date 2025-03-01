#include "Headers/Errors.hpp"

ParseError::ParseError(const Token& token, const std::string& message)
    : std::runtime_error(message) {}

RuntimeError::RuntimeError(Token token, const std::string& message)
    : token(std::move(token)), std::runtime_error(message) {}

BreakError::BreakError()
    : std::runtime_error("Using exception to break out of a loop.") {}

SyntaxError::SyntaxError(Token token, const std::string& message)
    : std::runtime_error(message), token(std::move(token)) {}