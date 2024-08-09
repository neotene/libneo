#ifndef NEO_TERM_STYLE
#define NEO_TERM_STYLE

#include <map>

#include "neo/term/ascii.hpp"

namespace neo {
namespace ui {
namespace term {

class style
{
   public:
    enum class element
    {
        vertical,
        horizontal,
        left_up_corner,
        right_up_corner,
        left_down_corner,
        right_down_corner,
    };

    using style_map = std::map<element, ascii>;

   private:
    style_map style_map_;
    static style_map const& fallback_style_map_;

   public:
    static style single_line;
    static style double_line;

   public:
    style(style_map const& style_map);

    ascii get(element element) const;
    style_map const& get_map() const;
};

}   // namespace term
}   // namespace ui
}   // namespace neo

#endif
