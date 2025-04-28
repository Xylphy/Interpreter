#pragma once
#include <initializer_list>
#include <string>

auto test_assertEqual(const std::string&& path, const std::string& expected)
    -> void;

auto test_assertEqualWithInput(const std::string&& path,
                                std::initializer_list<std::string> input,
                               const std::string&& expected) -> void;