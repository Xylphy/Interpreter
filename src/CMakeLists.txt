add_executable(Interpreter
  # Headers
  Headers/bisayaPP.hpp
  Headers/Environment.hpp
  Headers/Errors.hpp
  Headers/Expr.hpp
  Headers/Interpreter.hpp
  Headers/Parser.hpp
  Headers/Scanner.hpp
  Headers/Stmt.hpp
  Headers/Token.hpp

  # Sources
  bisayaPP.cpp
  Environment.cpp
  Errors.cpp
  Interpreter.cpp
  Parser.cpp
  Scanner.cpp
  Token.cpp
  utility.cpp
  main.cpp
)
