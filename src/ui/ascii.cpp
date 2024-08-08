#include <map>

#include "neo/term/curses.hpp"
#include "neo/ui/ascii.hpp"


namespace neo {
namespace ui {

std::map<term_char, decltype(u'│')> vt100_term_chars = {
    {term_char::vertical, u'│'},        {term_char::horizontal, u'─'},       {term_char::left_up_corner, u'┌'},
    {term_char::right_up_corner, u'┐'}, {term_char::left_down_corner, u'└'}, {term_char::right_down_corner, u'┘'},
};

std::map<term_char, wchar_t> basic_term_chars = {
    {term_char::vertical, '|'},        {term_char::horizontal, '-'},       {term_char::left_up_corner, '+'},
    {term_char::right_up_corner, '+'}, {term_char::left_down_corner, '+'}, {term_char::right_down_corner, '+'},
};
}   // namespace ui
}   // namespace neo