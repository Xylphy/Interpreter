#include "Headers/Lib/utility.hpp"

#include <any>
#include <functional>
#include <typeindex>

namespace utility {

auto anyToString(std::string& result, const std::any& value) noexcept -> void {
  result.append(anyToString(value));
}

auto anyToString(const std::any& value) noexcept -> std::string {
  static const std::unordered_map<std::type_index,
                                  std::function<std::string(const std::any&)>>
      typeToString{{typeid(int),
                    [](const std::any& value) -> std::string {
                      return std::to_string(std::any_cast<int>(value));
                    }},
                   {typeid(double),
                    [](const std::any& value) -> std::string {
                      return std::to_string(std::any_cast<double>(value));
                    }},
                   {typeid(std::string),
                    [](const std::any& value) -> std::string {
                      return std::any_cast<std::string>(value);
                    }},
                   {typeid(char),
                    [](const std::any& value) -> std::string {
                      return {1, std::any_cast<char>(value)};
                    }},
                   {typeid(bool), [](const std::any& value) -> std::string {
                      return std::any_cast<bool>(value) ? "true" : "false";
                    }}};

  auto iterator = typeToString.find(value.type());
  if (iterator != typeToString.end()) {
    return iterator->second(value);
  }
  return {};
}

auto convertData(const TokenType& type, std::any& value) -> void {
  if (type == TokenType::NUMBER) {
    value = std::any_cast<int>(value);
  } else if (type == TokenType::DECIMAL_NUMBER) {
    value = std::any_cast<double>(value);
  } else if (type == TokenType::STRING_LITERAL) {
    value = std::any_cast<std::string>(value);
  } else if (type == TokenType::CHARACTER_LITERAL) {
    value = std::any_cast<char>(value);
  } else if (type == TokenType::BOOL_TRUE) {
    value = std::any_cast<bool>(value);
  }
}

auto checkValidOperation(const std::any& left, TokenType type,
                         const std::any& right) -> bool {
  switch (type) {
    case TokenType::GREATER:
    case TokenType::GREATER_EQUAL:
    case TokenType::LESS:
    case TokenType::LESS_EQUAL:
    case TokenType::BANG_EQUAL:
    case TokenType::EQUAL_EQUAL:
    case TokenType::MINUS:
    case TokenType::PLUS:
    case TokenType::SLASH:
    case TokenType::STAR:
    case TokenType::MODULO:
      return isArithmetic(left) && isArithmetic(right);
    case TokenType::CONCATENATOR:
      return isConvertibleToString(left) && isConvertibleToString(right);
    default:
      return false;
  }
}

auto isConvertibleToString(const std::any& value) -> bool {
  const std::type_info& type = value.type();
  return isArithmetic(value) || type == typeid(std::string) ||
         type == typeid(char);
}

auto isArithmetic(const std::any& value) -> bool {
  const std::type_info& type = value.type();
  return type == typeid(int) || type == typeid(double);
}
}  // namespace utility