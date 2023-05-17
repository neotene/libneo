#include <algorithm>
#include <stdexcept>

#include <neo/term/buffer.hpp>
#include <neo/ui/print.hpp>

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
buffer::fill(character_type const &ch)
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

buffer::character_type &
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
        ascii_to(at(x + i, y).ch, ascii::box_horizontal_double);

    for (size_type i = 1; i < width - 1; ++i)
        ascii_to(at(x + i, y + height - 1).ch, ascii::box_horizontal_double);

    for (size_type i = 1; i < height - 1; ++i)
        ascii_to(at(x, y + i).ch, ascii::box_vertical_double);

    for (size_type i = 1; i < height - 1; ++i)
        ascii_to(at(x + width - 1, y + i).ch, ascii::box_vertical_double);

    ascii_to(at(x, y).ch, ascii::box_down_double_right_double);
    ascii_to(at(x, y + height - 1).ch, ascii::box_up_double_right_double);
    ascii_to(at(x + width - 1, y + height - 1).ch, ascii::box_up_double_left_double);
    ascii_to(at(x + width - 1, y).ch, ascii::box_down_double_left_double);
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
buffer::text(size_type const &x, size_type const &y, std::wstring const &text,
             std::pair<color, color> const &foreground_background)
{
    for (unsigned int i = 0; i < text.size(); ++i)
        at(x + i, y) = character(text[i], foreground_background.first, foreground_background.second);
}

}   // namespace terminal
}   // namespace ui
}   // namespace neo
