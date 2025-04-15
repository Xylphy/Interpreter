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
      "4OO5\n\x1"
      "c#last");
}

TEST(Sample_Programs, Test_4) {
  test_assertEqual("../../tests/source_files/Sample Programs/basic2.bpp", "25");
}

TEST(Sample_Programs, Test_5) {
  test_assertEqual("../../tests/source_files/Sample Programs/basic4.bpp",
                   "Ang average kay 10.000000");
}

TEST(Sample_Programs, Test_6) {
  test_assertEqual("../../tests/source_files/Sample Programs/basic5.bpp", "OO");
}

TEST(Sample_Programs, Test_7) {
  test_assertEqual(
      "../../tests/source_files/Sample Programs/basic6.bpp",
      "[line 2] Error at 'wrongType': Invalid assignment target.\n");
}

TEST(Sample_Programs, Test_8) {
  test_assertEqual(
      "../../tests/source_files/Sample Programs/basic7.bpp",
      "[line 2] Error at 'undefinedVar': Undefined variable 'undefinedVar'.\n");
}

TEST(Sample_Programs, Test_9) {
  test_assertEqual("../../tests/source_files/Sample Programs/basic9.bpp",
                   "[line 3] Error at 'x': Undefined variable 'x'.\n");
}

TEST(Sample_Programs, Test_10) {
  test_assertEqual("../../tests/source_files/Sample Programs/basic11.bpp",
                   "OO\nDILI\nOO\nOO\nOO\nOO\nDILI\nOO\n[line 10] Error at "
                   "'==': Invalid operation\n5\n5\n20\n5\n1\n");
}