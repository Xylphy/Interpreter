
#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Scopes/scope.bsy"
#else
#define FILE_PATH_1 "../../tests/source_files/Scopes/scope.bsy"
#endif

TEST(Interpreter, Scope) {
  test_assertEqual("../../tests/source_files/Scopes/scope.bsy",
                   "9\x1"
                   "dOO5\x1"
                   "dOO2\x1"
                   "cOO");
}

#undef FILE_PATH_1