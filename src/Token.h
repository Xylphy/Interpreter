#pragma once

#include <ostream>

class Token{
    public:
    friend std::ostream & operator<<(std::ostream &os, const Token &t);

};

std::ostream & operator<<(std::ostream &os, const Token &t);