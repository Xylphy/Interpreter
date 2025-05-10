#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 \
  "../../../tests/source_files/Additional Feature (While)/Test Case 1.bpp"
#define FILE_PATH_2 \
  "../../../tests/source_files/Additional Feature (While)/Test Case 2.bpp"
#else
#define FILE_PATH_1 \
  "../../tests/source_files/Additional Feature (While)/Test Case 1.bpp"
#define FILE_PATH_2 \
  "../../tests/source_files/Additional Feature (While)/Test Case 2.bpp"
#endif

TEST(WhileLoop, Test_1) {
  test_assertEqualWithInput(FILE_PATH_1, {"5"}, "2\n3\n4\n5\n");
}

TEST(WhileLoop, Test_2) {
  test_assertEqual(FILE_PATH_2, "2\n3\n4\n5\n6\n7\n8\n9\n10\n");
}

#undef FILE_PATH_1
#undef FILE_PATH_2