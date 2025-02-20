#pragma once

#include <any>
#include <string>

// This namespace contains utility functions that are used in the project.
namespace utility {

auto anyToString(std::string& result, const std::any& value) noexcept -> bool;

}  // namespace utility