#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Increment 3/Test Case 1.bpp"
#define FILE_PATH_2 "../../../tests/source_files/Increment 3/Test Case 2.bpp"
#define FILE_PATH_3 "../../../tests/source_files/Increment 3/Test Case 3.bpp"
#define FILE_PATH_4 "../../../tests/source_files/Increment 3/Test Case 4.bpp"
#define FILE_PATH_5 "../../../tests/source_files/Increment 3/Test Case 5.bpp"
#define FILE_PATH_6 "../../../tests/source_files/Increment 3/Test Case 6.bpp" 
#define FILE_PATH_7 "../../../tests/source_files/Increment 3/Test Case 7.bpp"
#else
#define FILE_PATH_1 "../../tests/source_files/Increment 3/Test Case 1.bpp"
#define FILE_PATH_2 "../../tests/source_files/Increment 3/Test Case 2.bpp"
#define FILE_PATH_3 "../../tests/source_files/Increment 3/Test Case 3.bpp"
#define FILE_PATH_4 "../../tests/source_files/Increment 3/Test Case 4.bpp"
#define FILE_PATH_5 "../../tests/source_files/Increment 3/Test Case 5.bpp"
#define FILE_PATH_6 "../../tests/source_files/Increment 3/Test Case 6.bpp"
#define FILE_PATH_7 "../../tests/source_files/Increment 3/Test Case 7.bpp"
#endif

TEST(Increment3, Test_1) {
  test_assertEqual(
      FILE_PATH_1,
      "[line 4] Error at 'SUGOD': Expect 'KATAPUSAN' at the end of the "
      "file.\nAn error occurred while parsing the source code.\n");
}

TEST(Increment3, Test_2) { test_assertEqual(FILE_PATH_2, ""); }

TEST(Increment3, Test_3) {
  test_assertEqual(
      FILE_PATH_3,
      "[line 3] Error at 'a': Variable not initialized.\nA runtime error "
      "occurred while interpreting the source code.\n");
}

TEST(Increment3, Test_4) {
  test_assertEqualWithInput(FILE_PATH_4, {"7"}, "-13");
}

TEST(Increment3, Test_5) {
  test_assertEqualWithInput(FILE_PATH_5, {"5"}, "-&8\x1*5\x1'");
}

TEST(Increment3, Test_6) {
  test_assertEqualWithInput(FILE_PATH_6, {"61"}, "Senior");
  test_assertEqualWithInput(FILE_PATH_6, {"21"}, "Adult");
  test_assertEqualWithInput(FILE_PATH_6, {"17"}, "Teen");
  test_assertEqualWithInput(FILE_PATH_6, {"8"}, "Child");
  test_assertEqualWithInput(FILE_PATH_6, {"0"}, "Toddler");
}

TEST(Increment3, Test_7) {
  test_assertEqualWithInput(FILE_PATH_7, {"10"}, "678910");
}


#undef FILE_PATH_1
#undef FILE_PATH_2
#undef FILE_PATH_3
#undef FILE_PATH_4
#undef FILE_PATH_5
#undef FILE_PATH_6
#undef FILE_PATH_7