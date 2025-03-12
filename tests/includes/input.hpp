#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Input, Test_1) {
  test_assertEqualWithInput("../../tests/source_files/Input/dawattest.bsy", "1, 2",
  "1 2");
}