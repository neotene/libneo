#include <curses.h>

#include <codecvt>
#include <cwchar>
#include <iostream>
#include <locale>
#include <map>
#include <string>

#include "neo/term/curses.hpp"
#include "neo/ui/color.hpp"
#include "neo/ui/print.hpp"

namespace neo {

std::map<color, int> colors = {
    {color::white, COLOR_WHITE}, {color::black, COLOR_BLACK}, {color::red, COLOR_RED},
    {color::green, COLOR_GREEN}, {color::blue, COLOR_BLUE},
};

std::map<std::string, size_t> color_pairs;

size_t current_pair_idx = 1;

void
print(unsigned int x, unsigned int y, std::basic_string<char16_t> const &text,
      std::pair<color, color> const &foreground_background)
{
    for (char16_t c : text)
        ::mvprintw(y, x++, "%s",
    // std::string hash = std::to_string(static_cast<int>(foreground_background.first)) +
    //                    std::to_string(static_cast<int>(foreground_background.second));

    // size_t pair_idx;

    // if (color_pairs.count(hash))
    //     pair_idx = color_pairs[hash];
    // else
    // {
    //     pair_idx = current_pair_idx;
    //     color_pairs[hash] = current_pair_idx;
    //     ++current_pair_idx;
    // }

    // ::init_pair(pair_idx, colors[foreground_background.first], colors[foreground_background.second]);
    // ::attron(COLOR_PAIR(pair_idx));
    // ::move(y, x);
    // std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> myconv;
    // // std::wstring ws(L"Your UTF-16 text");
    // std::string bs = myconv.to_bytes(text);
    // // std::cout << bs << '\n';
    // // ::move(y, x);
    // // std::cout << bs;
    // ::printw("%s", bs.data());
    // ::attroff(COLOR_PAIR(pair_idx));
}

}   // namespace neo
