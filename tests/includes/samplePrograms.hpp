#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Sample_Programs, Test_1) {
  test_assertEqual(
      "../../tests/source_files/Sample Programs/sample_program_1.bsy", "[-60]");
}

TEST(Sample_Programs, Test_2) {
  test_assertEqual(
      "../../tests/source_files/Sample Programs/sample_program_2.bsy", "OO");
}