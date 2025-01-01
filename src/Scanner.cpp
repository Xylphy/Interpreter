#include <sstream>

#include "Scanner.h"

std::vector<Token> Scanner::scanTokens() {
    std::vector<Token> tokens;

    std::istringstream stream(source);
    std::string word;

    while (stream >> word) {
        tokens.push_back(word);
    }

    return tokens;
}