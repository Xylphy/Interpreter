
#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Logical Expressions/logicalExpr.bsy"
#else
#define FILE_PATH_1 "../../tests/source_files/Logical Expressions/logicalExpr.bsy"
#endif

TEST(Interpreter, ShortCircuit) {
  test_assertEqual(
      "../../tests/source_files/Logical Expressions/logicalExpr.bsy", "HiYES");
}

#undef FILE_PATH_1