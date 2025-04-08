#pragma once
#include "AbstractScanner.hpp"

class InputScanner : private AbstractScanner {
 public:
  using AbstractScanner::scanTokens;

  InputScanner(std::string source, size_t line);

  auto scanToken() -> void override;
  auto identifier() -> void override;
};