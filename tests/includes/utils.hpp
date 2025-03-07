#pragma once
#include <string>

auto test_assertEqual(const std::string&& path, const std::string& expected)
    -> void;

auto test_assertEqualWithInput(const std::string&& path,
                               const std::string& input,
                               const std::string&& expected) -> void;