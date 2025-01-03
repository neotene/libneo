#ifndef NEO_TERM_TYPES
#define NEO_TERM_TYPES

namespace neo {
namespace ui {
namespace term {

using screen_size_t = unsigned int;

enum class anchor
{
    center,
    upper_left,
    upper_center,
    upper_right,
    right_center,
    lower_right,
    lower_center,
    lower_left,
    left_center
};

}   // namespace term
}   // namespace ui
}   // namespace neo

#endif
