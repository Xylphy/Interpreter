#include "Headers/Lib/utility.hpp"

#include <functional>
#include <typeindex>
#include <unordered_map>

namespace utility {

auto anyToString(std::string& result, const std::any& value) noexcept -> bool {
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
                   {typeid(char), [](const std::any& value) -> std::string {
                      return {1, std::any_cast<char>(value)};
                    }}};

  auto iterator = typeToString.find(value.type());
  if (iterator != typeToString.end()) {
    result.append(iterator->second(value));
    return true;
  }
  return false;
}
}  // namespace utility