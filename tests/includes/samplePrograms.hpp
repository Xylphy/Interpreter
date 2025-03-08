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

TEST(Sample_Programs, Test_3) {
  test_assertEqual(
      "../../tests/source_files/Sample Programs/sample_program_3.bsy",
      "4OO5\n\x1" "c#last");
}