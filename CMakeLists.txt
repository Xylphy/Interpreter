cmake_minimum_required(VERSION 3.31.3)

project(Lox)

set(CMAKE_CXX_STANDARD 26)
string(REPLACE "{" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -fsanitize=address")

add_executable(Interpreter
    "src/Abstract Syntax Tree/Expr.h"
    "src/Token.hpp"
    "src/Token.cpp"
    "src/Scanner.hpp"
    "src/Scanner.cpp"
    "src/interpreter.hpp"
    "src/interpreter.cpp"
    "src/main.cpp"
)