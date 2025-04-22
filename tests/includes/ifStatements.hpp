#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/If Statements/if1.bsy"
#define FILE_PATH_2 "../../../tests/source_files/If Statements/if2.bsy"
#else
#define FILE_PATH_1 "../../tests/source_files/If Statements/if1.bsy"
#define FILE_PATH_2 "../../tests/source_files/If Statements/if2.bsy"
#endif

TEST(If_Statements, Test_1) {
  test_assertEqual(FILE_PATH_1, "BAYOT SI JEREMY");
}

TEST(If_Statements, Test_2) { test_assertEqual(FILE_PATH_2, ""); }


#undef FILE_PATH_1
#undef FILE_PATH_2