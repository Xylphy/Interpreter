#pragma once

#include <string>

class Object {
public:
    virtual ~Object() {}
    virtual std::string toString() const = 0;
};