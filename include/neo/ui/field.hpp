#ifndef NEO_UI_FIELD
#define NEO_UI_FIELD

#include "neo/ui/attributes.hpp"
#include "neo/ui/color.hpp"
#include "neo/ui/input.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class CONTEXT>
class field : public object<CONTEXT>
{
   public:
    using parent_type = object<CONTEXT>;
    using typename parent_type::context_type;

   private:
    bool focused_;
    unsigned int size_;
    unsigned int seek_;
    std::vector<term_char_type> text_;
    bool is_password_;
    bool clear_on_hide_;

   public:
    field(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs, unsigned int size,
          bool is_password)
        : parent_type(ui_context, attrs, true)
        , focused_(false)
        , size_(size)
        , seek_(0)
        , is_password_(is_password)
        , clear_on_hide_(true)
    {
        text_.reserve(size);
    }

    virtual void draw(typename CONTEXT::buffer_type &buffer) override
    {
        std::pair<color, color> colors;

        if (focused_)
            colors = {color::black, color::white};
        else
            colors = {color::white, color::black};

        std::vector<term_char_type> to_print;
        if (!is_password_)
            to_print = text_;
        else
        {
            to_print = std::vector<term_char_type>();
            to_print.reserve(text_.size());
            for (int i = 0; i > text_.size(); ++i)
            {
                term_char_type ch;

                ch.attr = '*';
                to_print.push_back(ch);
            }
        }

        buffer.write(this->get_attributes().get_x(), this->get_attributes().get_y(), to_print, colors);

        std::vector<term_char_type> chs;

        chs.reserve(size_ - text_.size());

        for (int i = 0; i < size_ - text_.size(); ++i)
        {
            term_char_type ch;
            ch.attr = '_';
            chs.push_back(ch);
        }

        buffer.write(this->get_attributes().get_x() + text_.size(), this->get_attributes().get_y(), chs, colors);
    }

    virtual void update_focus(bool is_focused) override
    {
        focused_ = is_focused;
    }

    std::basic_string<typename CONTEXT::buffer_type::term_cell::char_type> const &text() const
    {
        return text_;
    }

    void on_input(input const &input) override
    {
        if (input.special(input::special_key::backspace) && !text_.empty())
            text_.pop_back();
        else if (input.printable() && text_.size() < size_)
        {
            term_char_type ch;

            ch.attr = input.key();
            text_.push_back(ch);
        }
    }
};

}   // namespace ui
}   // namespace neo

#endif
