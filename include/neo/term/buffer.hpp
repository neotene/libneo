#pragma once

#include <functional>
#include <string>
#include <vector>

#include <neo/config.hpp>
#include <neo/ui/ascii.hpp>
#include <neo/ui/color.hpp>

namespace neo {
namespace ui {
namespace terminal {

class NEO_API buffer
{
  public:
    struct character {
        using char_type = wchar_t;

        wchar_t ch;
        color ch_color;
        color bg_color;

        character(wchar_t ch_ = ' ', color ch_color_ = color::white, color bg_color_ = color::black)
            : ch(ch_)
            , ch_color(ch_color_)
            , bg_color(bg_color_)
        {}
    };

  public:
    using size_type = int;
    using character_type = character;
    using line_type = std::vector<character_type>;
    using buffer_type = std::vector<line_type>;

  private:
    buffer_type buffer_;

  public:
    void fill_area(size_type const &x, size_type const &y, size_type const &width, size_type const &height);
    void fill(character_type const &ch);
    void resize(size_type width, size_type height);
    character_type &at(size_type const &x, size_type const &y);
    void box(size_type const &x, size_type const &y, size_type const &width, size_type const &height);
    void for_each(std::function<void(line_type const &)> const &func) const;
    void for_each(std::function<void(line_type &)> const &func);
    void text(size_type const &x, size_type const &y, std::basic_string<character::char_type> const &text,
              std::pair<color, color> const &foreground_background = {color::white, color::black});
};

}   // namespace terminal
}   // namespace ui
}   // namespace neo
