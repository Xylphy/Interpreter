#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Loops/forLoop.bsy"
#else
#define FILE_PATH_1 "../../tests/source_files/Loops/forLoop.bsy"
#endif

TEST(ForLoop, TEST_1) {
  test_assertEqual(
      FILE_PATH_1,
      "0\n1\n1\n2\n3\n5\n8\n13\n21\n34\n55\n89\n144\n233\n377\n610\n987\n"
      "1597\n2584\n4181\n6765\n10946\n17711\n28657\n46368\n75025\n");
}

#undef FILE_PATH_1
#undef FILE_PATH_2