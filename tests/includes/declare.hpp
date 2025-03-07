#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Declare, Test_1) {
  test_assertEqual("../../tests/source_files/Declarations/declare.bsy", "5");
}

TEST(Declare, Test_2) {
  test_assertEqual("../../tests/source_files/Declarations/declare_2.bsy", "3");
}
