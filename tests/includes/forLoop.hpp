#include <gtest/gtest.h>

#include "utils.hpp"

TEST(Interpreter, FOR_LOOP) {
  test_assertEqual(
      "../../tests/source_files/Loops/forLoop.bsy",
      "0\n1\n1\n2\n3\n5\n8\n13\n21\n34\n55\n89\n144\n233\n377\n610\n987\n"
      "1597\n2584\n4181\n6765\n10946\n17711\n28657\n46368\n75025\n");
}