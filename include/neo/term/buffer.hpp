#ifndef NEO_TERM_BUFFER
#define NEO_TERM_BUFFER

#include <functional>
#include <string>
#include <vector>

#include "neo/config.hpp"
#include "neo/term/ascii.hpp"
#include "neo/term/style.hpp"
#include "neo/ui/color.hpp"

namespace neo {
namespace ui {
namespace term {

class NEO_API buffer
{
   public:
    struct cell {
        using char_type = std::remove_pointer<decltype(WACS_VLINE)>::type;

        char_type ch;
        color ch_color;
        color bg_color;

        cell(char_type ch_ = *WACS_PLUS, color ch_color_ = color::white, color bg_color_ = color::black)
            : ch(ch_)
            , ch_color(ch_color_)
            , bg_color(bg_color_)
        {}
    };

   public:
    using size_type = int;
    using sequence_type = std::vector<cell>;
    using line_type = sequence_type;
    using buffer_type = std::vector<line_type>;

   private:
    buffer_type buffer_;

   public:
    void fill_area(size_type const &x, size_type const &y, size_type const &width, size_type const &height);
    void fill(cell const &ch);
    void resize(size_type width, size_type height);
    cell &at(size_type const &x, size_type const &y);
    void box(size_type x, size_type y, size_type width, size_type height, style style = style::single_line);
    void for_each(std::function<void(line_type const &)> const &func) const;
    void for_each(std::function<void(line_type &)> const &func);
    void write(size_type const &x, size_type const &y, sequence_type &sequence);

    static buffer::cell::char_type buffer::get_character(ascii const &tc);
};

}   // namespace term
}   // namespace ui
}   // namespace neo

#endif
