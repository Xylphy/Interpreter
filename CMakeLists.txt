cmake_minimum_required(VERSION 3.31.3)

project(Lox)

set(CMAKE_CXX_STANDARD 26)

add_executable(Lox 
    "src/Abstract Syntax Tree/Expr.h"
    "src/Token.h"
    "src/Token.cpp"
    "src/Scanner.h"
    "src/Scanner.cpp"
    "src/cpplox.h"
    "src/cpplox.cpp"
    "src/main.cpp"
)

add_executable(Tool
    "tool/generateAst.h"
    "tool/generateAst.cpp"
    "tool/main.cpp"
)
