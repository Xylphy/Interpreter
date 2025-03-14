
#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Interpreter, ShortCircuit) {
  test_assertEqual(
      "../../tests/source_files/Logical Expressions/logicalExpr.bsy", "HiYES");
}