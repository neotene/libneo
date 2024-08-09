#include <algorithm>

#include "neo/term/ascii.hpp"
#include "neo/term/buffer.hpp"

namespace neo {
namespace ui {
namespace term {

buffer::cell::cell(char_type ch_, color ch_color_, color bg_color_)
    : ch(ch_)
    , ch_color(ch_color_)
    , bg_color(bg_color_)
{}

buffer::sequence_type
buffer::sequence::from_std_string(std::string const &std_string)
{
    sequence_type seq;

    seq.reserve(std_string.size());
    for (auto c : std_string)
        seq.push_back(cell::from_char(c));

    return seq;
}

void
buffer::fill_area(size_type const &x, size_type const &y, size_type const &width, size_type const &height)
{
    for (size_type i = 0; i < width; ++i)
        for (size_type j = 0; j < height; ++j)
        {
            cchar_t space_ch;

            space_ch.attr = ' ';
            at(i + x, j + y).ch = space_ch;
        }
}

void
buffer::fill(cell const &ch)
{
    for_each([&ch](line_type &line) { line = line_type(line.size(), ch); });
}

void
buffer::resize(size_type width, size_type height)
{
    buffer_.resize(height);
    for (line_type &line : buffer_)
        line.resize(width);
}

buffer::cell &
buffer::at(size_type const &x, size_type const &y)
{
    auto clamped_y = std::clamp(y, size_type(0), static_cast<size_type>(buffer_.size() - 1));
    auto clamped_x = std::clamp(x, size_type(0), static_cast<size_type>(buffer_[clamped_y].size() - 1));
    return buffer_[clamped_y][clamped_x];
}

void
buffer::box(size_type x, size_type y, size_type width, size_type height, style style)
{
    x--;
    y--;
    width++;
    height++;

    for (size_type i = 1; i < width - 1; ++i)
        at(x + i, y).ch = get_character(style.get(style::element::horizontal));

    for (size_type i = 1; i < width - 1; ++i)
        at(x + i, y + height - 1).ch = get_character(style.get(style::element::horizontal));

    for (size_type i = 1; i < height - 1; ++i)
        at(x, y + i).ch = get_character(style.get(style::element::vertical));

    for (size_type i = 1; i < height - 1; ++i)
        at(x + width - 1, y + i).ch = get_character(style.get(style::element::vertical));

    at(x, y).ch = get_character(style.get(style::element::left_up_corner));
    at(x, y + height - 1).ch = get_character(style.get(style::element::left_down_corner));
    at(x + width - 1, y + height - 1).ch = get_character(style.get(style::element::right_down_corner));
    at(x + width - 1, y).ch = get_character(style.get(style::element::right_up_corner));
}

void
buffer::for_each(std::function<void(line_type const &)> const &func) const
{
    for (line_type const &line : buffer_)
        func(line);
}

void
buffer::for_each(std::function<void(line_type &)> const &func)
{
    for (line_type &line : buffer_)
        func(line);
}

void
buffer::write(size_type const &x, size_type const &y, sequence_type &sequence)
{
    for (unsigned int i = 0; i < sequence.size(); ++i)
        at(x + i, y) = sequence[i];
}

std::map<ui::ascii, buffer::cell::char_type *> vt100_term_chars = {
    {ascii::box_vertical_light, WACS_VLINE},           {ascii::box_horizontal_light, WACS_HLINE},
    {ascii::box_up_light_left_light, WACS_ULCORNER},   {ascii::box_up_light_right_light, WACS_URCORNER},
    {ascii::box_down_light_left_light, WACS_LLCORNER}, {ascii::box_down_light_right_light, WACS_LRCORNER},
};

buffer::cell::char_type
buffer::get_character(ascii const &tc)
{
    return *vt100_term_chars.at(tc);
}

}   // namespace term
}   // namespace ui
}   // namespace neo
