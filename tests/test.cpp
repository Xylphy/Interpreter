#include <gtest/gtest.h>

#include "includes/forLoop.hpp"
#include "includes/declare.hpp"
#include "includes/ifStatements.hpp"
#include "includes/samplePrograms.hpp"
#include "includes/scope.hpp"
#include "includes/shortCircuit.hpp"


// TEST(Input, Test_1) {
//   test_assertEqualWithInput("../../tests/source_files/dawattest.bsy", "1",
//   "1");
// }

auto main(int argc, char* argv[]) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}