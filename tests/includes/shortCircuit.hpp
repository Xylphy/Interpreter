
#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 \
  "../../../tests/source_files/Logical Expressions/logicalExpr.bsy"
#else
#define FILE_PATH_1 \
  "../../tests/source_files/Logical Expressions/logicalExpr.bsy"
#endif

TEST(Interpreter, ShortCircuit) { test_assertEqual(FILE_PATH_1, "HiYES"); }

#undef FILE_PATH_1