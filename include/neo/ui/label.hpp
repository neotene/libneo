#ifndef NEO_UI_LABEL
#define NEO_UI_LABEL

#include <vector>

#include "neo/term/buffer.hpp"
#include "neo/ui/attributes.hpp"
#include "neo/ui/color.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class CONTEXT>
class label : public object<CONTEXT>
{
   public:
    using parent_type = object<CONTEXT>;
    using typename parent_type::context_type;

   private:
    std::string text_;
    color fg_;
    color bg_;

   public:
    label(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs,
          std::string const &text)
        : parent_type(ui_context, attrs)
        , text_(text)
        , fg_(color::white)
        , bg_(color::black)
    {
        text_.reserve(text.size());

        for (char c : text)
        {
            term_char_type ch;

            ch.attr = static_cast<decltype(ch.attr)>(c);
            text_.push_back(ch);
        }
    }

   public:
    virtual void update_focus(bool is_focused) override
    {}

    unsigned int size() const
    {
        return text_.size();
    }

    virtual void draw(typename CONTEXT::buffer_type &buffer) override
    {
        buffer.write(this->get_attributes().get_x(), this->get_attributes().get_y(),
                     buffer::sequence::from_std_string(text_));
    }

    void text(container_type const &text)
    {
        text_ = text;
    }

    void set_color(color const &fg, color const &bg)
    {
        fg_ = fg;
        bg_ = bg;
    }

    void on_input(input const &input) override
    {}
};

}   // namespace ui
}   // namespace neo

#endif
