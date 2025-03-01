#pragma once

#include "../Token.hpp"  // IWYU pragma: export

// This namespace contains utility functions that are used in the project.
namespace utility {

auto anyToString(std::string& result, const std::any& value) noexcept -> void;
auto anyToString(const std::any& value) noexcept -> std::string;
auto convertData(const TokenType& type, std::any& value) -> void;
auto isArithmetic(const std::any& value) -> bool;
auto isConvertibleToString(const std::any& value) -> bool;
auto checkValidOperation(const std::any& left, TokenType type,
                         const std::any& right) -> bool;
auto isAlpha(char character) noexcept -> bool;
auto isAlphaNumeric(char character) noexcept -> bool;
auto isDigit(char character) noexcept-> bool;
}  // namespace utility