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

TEST(Interpreter, Print) {
  test_assertEqual("../../tests/source_files/print.bsy", "[-60]");
}

TEST(Interpreter, FOR_LOOP) {
  test_assertEqual(
      "../../tests/source_files/forLoop.bsy",
      "0\n1\n1\n2\n3\n5\n8\n13\n21\n34\n55\n89\n144\n233\n377\n610\n987\n"
      "1597\n2584\n4181\n6765\n10946\n17711\n28657\n46368\n75025\n");
}

TEST(Interpreter, Declare) {
  test_assertEqual("../../tests/source_files/declare.bsy", "5");
}

TEST(Interpreter, Scope) {
  test_assertEqual("../../tests/source_files/scope.bsy",
                   "9\x1"
                   "dOO5\x1"
                   "dOO2\x1"
                   "cOO");
}

TEST(Interpreter, ShortCircuit) {
  test_assertEqual("../../tests/source_files/logicalExpr.bsy", "HiYES");
}

TEST(Interpreter, Input) {
  test_assertEqualWithInput("../../tests/source_files/dawattest.bsy", "1", "1");
}

auto main(int argc, char* argv[]) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}