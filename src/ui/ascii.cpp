#include "neo/ui/ascii.hpp"

namespace neo {
namespace ui {

std::map<term_char, ascii> default_term_chars = {
    {term_char::vertical, ascii::box_vertical_light},
    {term_char::horizontal, ascii::box_horizontal_light},
    {term_char::left_up_corner, ascii::box_down_light_right_light},
    {term_char::right_up_corner, ascii::box_down_light_left_light},
    {term_char::left_down_corner, ascii::box_up_light_right_light},
    {term_char::right_down_corner, ascii::box_up_light_left_light},
};

std::map<term_char, wchar_t> xterm_term_chars = {
    {term_char::vertical, '|'},        {term_char::horizontal, '-'},       {term_char::left_up_corner, '+'},
    {term_char::right_up_corner, '+'}, {term_char::left_down_corner, '+'}, {term_char::right_down_corner, '+'},
};
}   // namespace ui
}   // namespace neo