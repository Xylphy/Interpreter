#include <gtest/gtest.h>

#include "includes/declare.hpp"
#include "includes/forLoop.hpp"
#include "includes/ifStatements.hpp"
#include "includes/increment.hpp"
#include "includes/increment2.hpp"
#include "includes/input.hpp"
#include "includes/samplePrograms.hpp"
#include "includes/scope.hpp"
#include "includes/shortCircuit.hpp"

auto main(int argc, char* argv[]) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}