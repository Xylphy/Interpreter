#include <gtest/gtest.h>

#include "utils.hpp"

#if defined(_MSC_VER)
#define FILE_PATH_1 "../../../tests/source_files/Input/dawattest.bsy"
#else
#define FILE_PATH_1 "../../tests/source_files/Input/dawattest.bsy"
#endif

TEST(Input, Test_1) { test_assertEqualWithInput(FILE_PATH_1, {"1, 2"}, "1 2"); }

#undef FILE_PATH_1