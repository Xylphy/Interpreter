#include <gtest/gtest.h>

#include "includes/forLoop.hpp"
#include "includes/declare.hpp"
#include "includes/ifStatements.hpp"
#include "includes/samplePrograms.hpp"
#include "includes/scope.hpp"
#include "includes/shortCircuit.hpp"
#include "includes/input.hpp"

auto main(int argc, char* argv[]) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}