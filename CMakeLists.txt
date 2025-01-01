cmake_minimum_required(VERSION 3.31.3)

project(Lox)

set(CMAKE_CXX_STANDARD 26)

add_executable(Lox 
    "src/Token.h"
    "src/Token.cpp"
    "src/Scanner.h"
    "src/Scanner.cpp"
    "src/lox.h"
    "src/lox.cpp"
    "src/main.cpp"
)