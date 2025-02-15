#include <stdexcept>

class ParseError: public std::runtime_error {
   public:
    ParseError(std::string message) :
        std::runtime_error(message),
        message(message) {}

    const char* what() const noexcept override { return message.c_str(); }

   private:
    std::string message;
};