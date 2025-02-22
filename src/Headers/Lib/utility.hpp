#pragma once

#include <any>
#include <exception>
#include <print>
#include <stdexcept>
#include <string>

#include "../Token.hpp"  // IWYU pragma: export

// This namespace contains utility functions that are used in the project.
namespace utility {

auto anyToString(std::string& result, const std::any& value) noexcept -> void;
auto anyToString(const std::any& value) noexcept -> std::string;

template <typename T, typename U>
auto addNumerics(const T& left, const U& right) -> decltype(left + right) {
  return left + right;
}

template <typename T, typename U>
auto subtractNumerics(const T& left, const U& right) -> decltype(left - right) {
  return left - right;
}

template <typename T, typename U>
auto multiplyNumerics(const T& left, const U& right) -> decltype(left * right) {
  return left * right;
}

template <typename T, typename U>
auto divideNumerics(const T& left, const U& right) -> decltype(left / right) {
  try {
    return left / right;
  } catch (const std::exception& e) {
    throw std::runtime_error("Division by zero");
  }
}

template <typename T, typename U>
auto moduloNumerics(const T& left, const U& right) -> decltype(left % right) {
  return left % right;
}

template <typename T, typename U>
auto greaterThan(const T& left, const U& right) -> bool {
  return left > right;
}

template <typename T, typename U>
auto greaterThanOrEqual(const T& left, const U& right) -> bool {
  return left >= right;
}

template <typename T, typename U>
auto lessThan(const T& left, const U& right) -> bool {
  return left < right;
}

template <typename T, typename U>
auto lessThanOrEqual(const T& left, const U& right) -> bool {
  return left <= right;
}

template <typename T, typename U>
auto notEqual(const T& left, const U& right) -> bool {
  return left != right;
}

template <typename T, typename U>
auto equal(const T& left, const U& right) -> bool {
  return left == right;
}

auto isArithmetic(const std::any& value) -> bool;

auto isConvertibleToString(const std::any& value) -> bool;

// This function checks if the operation is valid for the given operands.
auto checkValidOperation(const std::any& left, TokenType type,
                         const std::any& right) -> bool;

}  // namespace utility