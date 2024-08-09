#ifndef NEO_UI_BUTTON
#define NEO_UI_BUTTON

#include <functional>
#include <string>

#include "neo/ui/attributes.hpp"
#include "neo/ui/color.hpp"
#include "neo/ui/input.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

struct window_impl;

template <class CONTEXT>
class button : public object<CONTEXT>
{
   public:
    using parent_type = object<CONTEXT>;
    // using dimension_type = typename parent_type::context_type::buffer_type::size_type;
    // using coord_type = typename parent_type::coord_type;
    using typename parent_type::context_type;

   public:
    using activate_proto = void();
    using activate_callback = std::function<activate_proto>;

   private:
    std::basic_string<typename CONTEXT::buffer_type::term_cell::char_type> text_;
    activate_callback on_activate_;
    bool focused_;

   public:
    button(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs,
           std::basic_string<typename CONTEXT::buffer_type::term_cell::char_type> const &text,
           activate_callback const &on_activate)
        : parent_type(ui_context, attrs, true)
        , text_(text)
        , focused_(false)
        , on_activate_(on_activate)
    {}

    virtual void draw(typename CONTEXT::buffer_type &buffer) override
    {
        buffer.box(this->get_attributes().get_x() - 1, this->get_attributes().get_y() - 1,
                   static_cast<typename CONTEXT::buffer_type::size_type>(text_.size() + 2), 3);
        if (!focused_)
            buffer.text(this->get_attributes().get_x(), this->get_attributes().get_y(), text_,
                        {color::white, color::black});
        else
            buffer.text(this->get_attributes().get_x(), this->get_attributes().get_y(), text_,
                        {color::black, color::white});
    }

    virtual void update_focus(bool is_focused) override
    {
        focused_ = is_focused;
    }

    void on_input(input const &input) override
    {
        if (focused_ && input.special(input::special_key::enter))
            on_activate_();
    }
};

}   // namespace ui
}   // namespace neo

#endif
