#include "neo/term/style.hpp"

namespace neo {
namespace ui {
namespace term {

style style::single_line({
    {vertical, ascii::box_vertical_light},
    {horizontal, ascii::box_horizontal_light},
    {left_up_corner, ascii::box_up_light_left_light},
    {right_up_corner, ascii::box_up_light_right_light},
    {left_down_corner, ascii::box_down_light_left_light},
    {right_down_corner, ascii::box_down_light_right_light},
});

style style::double_line({
    {vertical, ascii::box_vertical_light},
    {horizontal, ascii::box_horizontal_light},
    {left_up_corner, ascii::box_up_light_left_light},
    {right_up_corner, ascii::box_up_light_right_light},
    {left_down_corner, ascii::box_down_light_left_light},
    {right_down_corner, ascii::box_down_light_right_light},
});

style::style_map const& style::fallback_style_map_ = style::single_line.get_map();

}   // namespace term
}   // namespace ui
}   // namespace neo