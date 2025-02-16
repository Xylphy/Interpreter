#include <stdexcept>

class ParseError : public std::runtime_error {
 public:
  ParseError(const std::string& message)
      : std::runtime_error(message), message(message) {}

  [[nodiscard]] auto what() const noexcept -> const char* override { return message.c_str(); }

 private:
  std::string message;
};