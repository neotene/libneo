#pragma once

#include <cassert>

#include <stack>
#include <string>
#include <tuple>

#include <neo/ui/color.hpp>

namespace neo {

void print(unsigned int x, unsigned int y, std::wstring const &text,
           std::pair<color, color> const &foreground_background = {color::white, color::black});

}   // namespace neo
