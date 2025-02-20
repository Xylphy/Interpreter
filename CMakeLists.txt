cmake_minimum_required(VERSION 3.31.3)

project(Interpreter)

set(CMAKE_CXX_STANDARD 26)
# string(REPLACE "{" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -fsanitize=address")

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  file(GLOB_RECURSE ALL_SOURCE_FILES
    src/*.cpp src/Headers/*.hpp
  )

  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
    COMMENT "Formatting code with clang-format..."
  )
endif()

# Enable AddressSanitizer (ASan)
# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
#   # Add flags for both compile and link stages
#   add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
#   add_link_options(-fsanitize=address -fno-omit-frame-pointer)
# endif()

# Enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,readability-*,modernize-*,performance-*,clang-analyzer-*")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,performance-*")

add_executable(Interpreter
  #Headers
  "src/Headers/Interpreter.hpp"
  "src/Headers/Parser.hpp"
  "src/Headers/Token.hpp"
  "src/Headers/Expr.hpp"
  "src/Headers/Scanner.hpp"
  "src/Headers/bisayaPP.hpp"
  "src/Headers/AstPrinter.hpp"
  "src/Headers/Errors.hpp"
  "src/Headers/Lib/utility.hpp"
  "src/Headers/Stmt.hpp"

  #Source
  "src/Interpreter.cpp"
  "src/utility.cpp"
  "src/Errors.cpp"
  "src/Parser.cpp"
  "src/Token.cpp"
  "src/AstPrinter.cpp"
  "src/Scanner.cpp"
  "src/bisayaPP.cpp"
  "src/main.cpp"
)

add_executable(Tool
  "tool/generateAst.hpp"
  "tool/generateAst.cpp"
  "tool/main.cpp"
)

