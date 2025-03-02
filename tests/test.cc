#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <streambuf>

#include "../src/Headers/bisayaPP.hpp"

TEST(Interpreter, Multiple_Variable_Declaration) {
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  BisayaPP::runFile("../../tests/source_files/print.bsy");

  std::cout.rdbuf(old);
  ASSERT_EQ(buffer.str(), "[-60]");
}

// TEST(Interpreter, FOR_LOOP){
//     std::stringstream buffer;
//     std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
//     BisayaPP::runFile("../../tests/source_files/for_loop.bsy");
    
//     std::cout.rdbuf(old);
//     ASSERT_EQ(buffer.str(), "0\n1\n2\n3\n4\n");
// }


auto main(int argc, char *argv[]) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}