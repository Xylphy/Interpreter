#include <gtest/gtest.h>

#include "utils.hpp"

TEST(If_Statements, Test_1) {
  test_assertEqual("../../tests/source_files/If Statements/if1.bsy",
                   "BAYOT SI JEREMY");
}

TEST(If_Statements, Test_2) {
  test_assertEqual("../../tests/source_files/If Statements/if2.bsy", "");
}
