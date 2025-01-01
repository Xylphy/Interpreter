#include <sstream>

#include "Scanner.h"

std::vector<std::string> Scanner::scanTokens() {
    std::vector<std::string> tokens;

    std::istringstream stream(source);
    std::string word;

    while (stream >> word) {
        tokens.push_back(word);
    }

    return tokens;
}