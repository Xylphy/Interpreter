cmake_minimum_required(VERSION 3.31.3)

project(Lox)

set(CMAKE_CXX_STANDARD 26)
# string(REPLACE "{" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -fsanitize=address")

add_executable(Interpreter
    "src/Headers/Parser.hpp"
    "src/Headers/Token.hpp"
    "src/Headers/Expr.hpp"
    "src/Headers/Scanner.hpp"
    "src/Headers/interpreter.hpp"
    "src/Headers/AstPrinter.hpp"
    "src/Headers/Stmt.hpp"
    "src/Headers/ParseError.hpp"
    "src/ParseError.cpp"
    "src/Parser.cpp"
    "src/Token.cpp"
    "src/AstPrinter.cpp"
    "src/Scanner.cpp"
    "src/interpreter.cpp"
    "src/main.cpp"
)

add_executable(Tool
    "tool/generateAst.hpp"
    "tool/generateAst.cpp"
    "tool/main.cpp"
)
