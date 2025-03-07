#include "includes/utils.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <streambuf>

#include "../src/Headers/bisayaPP.hpp"

auto test_assertEqual(const std::string&& path, const std::string& expected)
    -> void {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  BisayaPP::runFile(path.c_str());

  std::cout.rdbuf(old);

  ASSERT_EQ(buffer.str(), expected);
}

auto test_assertEqualWithInput(const std::string&& path,
                               const std::string& input,
                               const std::string&& expected) -> void {
  std::stringstream inputBuffer(input);
  std::streambuf* oldIn = std::cin.rdbuf(inputBuffer.rdbuf());

  std::stringstream outputBuffer;
  std::streambuf* oldOut = std::cout.rdbuf(outputBuffer.rdbuf());

  BisayaPP::runFile(path.c_str());

  std::cin.rdbuf(oldIn);
  std::cout.rdbuf(oldOut);

  ASSERT_EQ(outputBuffer.str(), expected);
}
