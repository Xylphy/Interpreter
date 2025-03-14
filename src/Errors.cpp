#include "Headers/Errors.hpp"

ParseError::ParseError(const Token& token, const std::string& message)
    : std::runtime_error(message) {}

RuntimeError::RuntimeError(const Token& token, const std::string& message)
    : std::runtime_error(message), token(token) {}

BreakError::BreakError()
    : std::runtime_error("Using exception to break out of a loop.") {}

SyntaxError::SyntaxError(const Token& token, const std::string& message)
    : std::runtime_error(message), token(token) {}