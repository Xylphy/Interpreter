#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Increment/Test Case 1.bpp"
#define FILE_PATH_2 "../../../tests/source_files/Increment/Test Case 2.bpp"
#define FILE_PATH_3 "../../../tests/source_files/Increment/Test Case 3.bpp"
#define FILE_PATH_4 "../../../tests/source_files/Increment/Test Case 4.bpp"
#define FILE_PATH_5 "../../../tests/source_files/Increment/Test Case 5.bpp"
#define FILE_PATH_6 "../../../tests/source_files/Increment/Test Case 6.bpp"
#define FILE_PATH_7 "../../../tests/source_files/Increment/Test Case 7.bpp"
#define FILE_PATH_8 "../../../tests/source_files/Increment/Test Case 8.bpp"
#define FILE_PATH_9 "../../../tests/source_files/Increment/Test Case 9.bpp"
#define FILE_PATH_10 "../../../tests/source_files/Increment/Test Case 10.bpp"
#define FILE_PATH_11 "../../../tests/source_files/Increment/Test Case 11.bpp"
#define FILE_PATH_12 "../../../tests/source_files/Increment/Test Case 12.bpp"
#else
#define FILE_PATH_1 "../../tests/source_files/Increment/Test Case 1.bpp"
#define FILE_PATH_2 "../../tests/source_files/Increment/Test Case 2.bpp"
#define FILE_PATH_3 "../../tests/source_files/Increment/Test Case 3.bpp"
#define FILE_PATH_4 "../../tests/source_files/Increment/Test Case 4.bpp"
#define FILE_PATH_5 "../../tests/source_files/Increment/Test Case 5.bpp"
#define FILE_PATH_6 "../../tests/source_files/Increment/Test Case 6.bpp"
#define FILE_PATH_7 "../../tests/source_files/Increment/Test Case 7.bpp"
#define FILE_PATH_8 "../../tests/source_files/Increment/Test Case 8.bpp"
#define FILE_PATH_9 "../../tests/source_files/Increment/Test Case 9.bpp"
#define FILE_PATH_10 "../../tests/source_files/Increment/Test Case 10.bpp"
#define FILE_PATH_11 "../../tests/source_files/Increment/Test Case 11.bpp"
#define FILE_PATH_12 "../../tests/source_files/Increment/Test Case 12.bpp"
#endif

TEST(Increment, Test_1) { test_assertEqual(FILE_PATH_1, ""); }

TEST(Increment, Test_2) {
  test_assertEqual(FILE_PATH_2,
                   "[line 3] Error at 'NUMERO': Expect variable name.\n");
}

TEST(Increment, Test_3) {
  test_assertEqual(FILE_PATH_3,
                   "[line 2] Error at '7': Expect variable name.\n");
}

TEST(Increment, Test_4) { test_assertEqual(FILE_PATH_4, ""); }

TEST(Increment, Test_5) { test_assertEqual(FILE_PATH_5, ""); }

TEST(Increment, Test_6) { test_assertEqual(FILE_PATH_6, "-5"); }

TEST(Increment, Test_7) { test_assertEqual(FILE_PATH_7, "-2"); }

TEST(Increment, Test_8) { test_assertEqual(FILE_PATH_8, "&-5&2&"); }

TEST(Increment, Test_9) {
  test_assertEqual(FILE_PATH_9,
                   "\x1"
                   "a\x1"
                   "b");
}

TEST(Increment, Test_10) {
  test_assertEqual(FILE_PATH_10,
                   "[line 5] Error at 'b': Expect newline after value.\n\x1"
                   "a");
}

TEST(Increment, TEST_11) {
  test_assertEqualWithInput(FILE_PATH_11, {"7", "2"}, "9");
}

TEST(Increment, TEST_12) {
  test_assertEqualWithInput(FILE_PATH_12, {"\"OO\""}, "DILI");
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
#undef FILE_PATH_11
#undef FILE_PATH_12