#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 \
  "../../../tests/source_files/Sample Programs/sample_program_1.bsy"
#define FILE_PATH_2 \
  "../../../tests/source_files/Sample Programs/sample_program_2.bsy"
#define FILE_PATH_3 \
  "../../../tests/source_files/Sample Programs/sample_program_3.bsy"
#define FILE_PATH_4 "../../../tests/source_files/Sample Programs/basic2.bpp"
#define FILE_PATH_5 "../../../tests/source_files/Sample Programs/basic4.bpp"
#define FILE_PATH_6 "../../../tests/source_files/Sample Programs/basic5.bpp"
#define FILE_PATH_7 "../../../tests/source_files/Sample Programs/basic6.bpp"
#define FILE_PATH_8 "../../../tests/source_files/Sample Programs/basic7.bpp"
#define FILE_PATH_9 "../../../tests/source_files/Sample Programs/basic9.bpp"
#define FILE_PATH_10 "../../../tests/source_files/Sample Programs/basic11.bpp"
#else
#define FILE_PATH_1 \
  "../../tests/source_files/Sample Programs/sample_program_1.bsy"
#define FILE_PATH_2 \
  "../../tests/source_files/Sample Programs/sample_program_2.bsy"
#define FILE_PATH_3 \
  "../../tests/source_files/Sample Programs/sample_program_3.bsy"
#define FILE_PATH_4 "../../tests/source_files/Sample Programs/basic2.bpp"
#define FILE_PATH_5 "../../tests/source_files/Sample Programs/basic4.bpp"
#define FILE_PATH_6 "../../tests/source_files/Sample Programs/basic5.bpp"
#define FILE_PATH_7 "../../tests/source_files/Sample Programs/basic6.bpp"
#define FILE_PATH_8 "../../tests/source_files/Sample Programs/basic7.bpp"
#define FILE_PATH_9 "../../tests/source_files/Sample Programs/basic9.bpp"
#define FILE_PATH_10 "../../tests/source_files/Sample Programs/basic11.bpp"

#endif

TEST(Sample_Programs, Test_1) { test_assertEqual(FILE_PATH_1, "[-60\x1]"); }

TEST(Sample_Programs, Test_2) { test_assertEqual(FILE_PATH_2, "OO"); }

TEST(Sample_Programs, Test_3) {
  test_assertEqual(FILE_PATH_3,
                   "4OO5\n\x1"
                   "c\x1#last");
}

TEST(Sample_Programs, Test_4) { test_assertEqual(FILE_PATH_4, "25"); }

TEST(Sample_Programs, Test_5) {
  test_assertEqual(FILE_PATH_5, "Ang average kay 10.000000");
}

TEST(Sample_Programs, Test_6) { test_assertEqual(FILE_PATH_6, "OO"); }

TEST(Sample_Programs, Test_7) {
  test_assertEqual(
      FILE_PATH_7,
      "[line 2] Error at 'wrongType': Invalid assignment target.\nA runtime "
      "error occurred while interpreting the source code.\n");
}

TEST(Sample_Programs, Test_8) {
  test_assertEqual(
      FILE_PATH_8,
      "[line 2] Error at 'undefinedVar': Undefined variable 'undefinedVar'.\nA "
      "runtime error occurred while interpreting the source code.\n");
}

TEST(Sample_Programs, Test_9) {
  test_assertEqual(FILE_PATH_9,
                   "[line 3] Error at 'x': Undefined variable 'x'.\nA runtime "
                   "error occurred while interpreting the source code.\n");
}

TEST(Sample_Programs, Test_10) {
  test_assertEqual(FILE_PATH_10,
                   "DILI\nOO\nDILI\nOO\nOO\nOO\nOO\nDILI\nOO\n[line 10] Error "
                   "at '==': Invalid operation\nA runtime error occurred while "
                   "interpreting the source code.\n");
}

#undef FILE_PATH_1
#undef FILE_PATH_2
#undef FILE_PATH_3
#undef FILE_PATH_4
#undef FILE_PATH_5
#undef FILE_PATH_6
#undef FILE_PATH_7
#undef FILE_PATH_8
#undef FILE_PATH_9
#undef FILE_PATH_10