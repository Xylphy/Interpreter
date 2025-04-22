#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Declarations/declare.bsy"
#define FILE_PATH_2 "../../../tests/source_files/Declarations/declare_2.bsy"
#else
#define FILE_PATH_1 "../../tests/source_files/Declarations/declare.bsy"
#define FILE_PATH_2 "../../tests/source_files/Declarations/declare_2.bsy"
#endif

TEST(Declare, Test_1) { test_assertEqual(FILE_PATH_1, "5"); }

TEST(Declare, Test_2) { test_assertEqual(FILE_PATH_2, "3"); }

#undef FILE_PATH_1
#undef FILE_PATH_2