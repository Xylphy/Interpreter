#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Increment 2/Test Case 1.bpp"
#define FILE_PATH_2 "../../../tests/source_files/Increment 2/Test Case 2.bpp"
#define FILE_PATH_3 "../../../tests/source_files/Increment 2/Test Case 3.bpp"
#define FILE_PATH_4 "../../../tests/source_files/Increment 2/Test Case 4.bpp"
#define FILE_PATH_5 "../../../tests/source_files/Increment 2/Test Case 5.bpp"
#define FILE_PATH_6 "../../../tests/source_files/Increment 2/Test Case 6.bpp"
#else
#define FILE_PATH_1 "../../tests/source_files/Increment 2/Test Case 1.bpp"
#define FILE_PATH_2 "../../tests/source_files/Increment 2/Test Case 2.bpp"
#define FILE_PATH_3 "../../tests/source_files/Increment 2/Test Case 3.bpp"
#define FILE_PATH_4 "../../tests/source_files/Increment 2/Test Case 4.bpp"
#define FILE_PATH_5 "../../tests/source_files/Increment 2/Test Case 5.bpp"
#define FILE_PATH_6 "../../tests/source_files/Increment 2/Test Case 6.bpp"
#endif

TEST(Increment_2, Test_1) {
  test_assertEqualWithInput(FILE_PATH_1, {"1"}, "11");
  test_assertEqualWithInput(FILE_PATH_1, {"12"}, "");
}

TEST(Increment_2, Test_2) {
  test_assertEqualWithInput(FILE_PATH_2, {"'c'"},
                            "\x1"
                            "c");
  test_assertEqualWithInput(FILE_PATH_2, {"'a'"}, "");
}

TEST(Increment_2, Test_3) {
  test_assertEqualWithInput(FILE_PATH_3, {"1"}, "\x1p");
  test_assertEqualWithInput(FILE_PATH_3, {"-1"}, "\x1n");
  test_assertEqualWithInput(FILE_PATH_3, {"0"}, "\x1z");
}

TEST(Increment_2, Test_4) { test_assertEqual(FILE_PATH_4, "1\n2\n3\n4\n5\n"); }

TEST(Increment_2, Test_5) {
  test_assertEqual(
      FILE_PATH_5,
      "\x1x\n\x1x\x1x\n\x1x\x1x\x1x\n\x1x\x1x\x1x\x1x\n\x1x\x1x\x1x\x1x\x1x\n");
}

TEST(Increment_2, Test_6) {
  test_assertEqual(FILE_PATH_6, "1\n22\n333\n4444\n55555\n");
}

#undef FILE_PATH_1
#undef FILE_PATH_2
#undef FILE_PATH_3
#undef FILE_PATH_4
#undef FILE_PATH_5
#undef FILE_PATH_6