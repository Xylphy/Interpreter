cmake_minimum_required(VERSION 3.31.3)

project(Lox)

set(CMAKE_CXX_STANDARD 26)

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

add_executable(Tool
    "tool/generateAst.h"
    "tool/generateAst.cpp"
    "tool/main.cpp"
)
