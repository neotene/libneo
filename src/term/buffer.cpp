#include "neo/term/buffer.hpp"

#include <algorithm>

#include "neo/ui/ascii.hpp"

namespace neo {
namespace ui {
namespace terminal {

void
buffer::fill_area(size_type const &x, size_type const &y, size_type const &width, size_type const &height)
{
    for (size_type i = 0; i < width; ++i)
        for (size_type j = 0; j < height; ++j)
            at(i + x, j + y) = ' ';
}

void
buffer::fill(cell_type const &ch)
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

buffer::cell_type &
buffer::at(size_type const &x, size_type const &y)
{
    auto clamped_y = std::clamp(y, size_type(0), static_cast<size_type>(buffer_.size() - 1));
    auto clamped_x = std::clamp(x, size_type(0), static_cast<size_type>(buffer_[clamped_y].size() - 1));
    return buffer_[clamped_y][clamped_x];
}

void
buffer::box(size_type const &x, size_type const &y, size_type const &width, size_type const &height)
{
    for (size_type i = 1; i < width - 1; ++i)
        at(x + i, y).ch = get_character(term_char::horizontal);

    for (size_type i = 1; i < width - 1; ++i)
        at(x + i, y + height - 1).ch = get_character(term_char::horizontal);

    for (size_type i = 1; i < height - 1; ++i)
        at(x, y + i).ch = get_character(term_char::vertical);

    for (size_type i = 1; i < height - 1; ++i)
        at(x + width - 1, y + i).ch = get_character(term_char::vertical);

    at(x, y).ch = get_character(term_char::left_down_corner);
    at(x, y + height - 1).ch = get_character(term_char::right_down_corner);
    at(x + width - 1, y + height - 1).ch = get_character(term_char::left_up_corner);
    at(x + width - 1, y).ch = get_character(term_char::right_down_corner);
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
buffer::text(size_type const &x, size_type const &y, std::basic_string<term_cell::char_type> const &text,
             std::pair<color, color> const &foreground_background)
{
    for (unsigned int i = 0; i < text.size(); ++i)
        at(x + i, y) = term_cell(text[i], foreground_background.first, foreground_background.second);
}

}   // namespace terminal
}   // namespace ui
}   // namespace neo
