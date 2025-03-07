
#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Interpreter, ShortCircuit) {
  test_assertEqual("../../tests/source_files/logicalExpr.bsy", "HiYES");
}