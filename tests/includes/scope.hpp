
#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Interpreter, Scope) {
  test_assertEqual("../../tests/source_files/Scopes/scope.bsy",
                   "9\x1"
                   "dOO5\x1"
                   "dOO2\x1"
                   "cOO");
}
