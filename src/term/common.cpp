#include <map>
#include <neo/term/curses.hpp>
#include <string>

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
print(unsigned int x, unsigned int y, std::wstring const &text, std::pair<color, color> const &foreground_background)
{
    std::string hash = std::to_string(static_cast<int>(foreground_background.first)) +
                       std::to_string(static_cast<int>(foreground_background.second));

    size_t pair_idx;

    if (color_pairs.count(hash))
        pair_idx = color_pairs[hash];
    else
    {
        pair_idx = current_pair_idx;
        color_pairs[hash] = current_pair_idx;
        ++current_pair_idx;
    }

    ::init_pair(pair_idx, colors[foreground_background.first], colors[foreground_background.second]);
    ::attron(COLOR_PAIR(pair_idx));
    ::mvprintw(y, x, "%ls", text.data());
    ::attroff(COLOR_PAIR(pair_idx));
}

}   // namespace neo
