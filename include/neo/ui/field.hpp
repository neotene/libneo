#pragma once

#include <neo/config.hpp>

#include <neo/ui/attributes.hpp>
#include <neo/ui/input.hpp>
#include <neo/ui/object.hpp>

namespace neo {
namespace ui {

template <class CONTEXT>
class field : public object<CONTEXT>
{
  public:
    using parent_type = object<CONTEXT>;
    using dimension_type = typename parent_type::context_type::buffer_type::size_type;
    using coord_type = typename parent_type::coord_type;
    using typename parent_type::context_type;

  private:
    bool focused_;
    unsigned int size_;
    unsigned int seek_;
    std::wstring text_;
    bool is_password_;
    bool clear_on_hide_;

  public:
    field(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs, unsigned int size,
          bool is_password, frame<CONTEXT> *parent = nullptr)
        : parent_type(ui_context, attrs, true)
        , focused_(false)
        , size_(size)
        , seek_(0)
        , is_password_(is_password)
        , clear_on_hide_(true)
    {
        text_.reserve(size);

        if (!parent)
            return;
        parent->add_child(this);

        this->on_focus_change([this](bool focused) { this->focused_ = focused; });

        this->on_input([this](input const &input) {
            if (input.special(input::special_key::backspace) && !text_.empty())
                text_.pop_back();
            else if (input.printable() && text_.size() < size_)
                text_.push_back(input.key());
        });
    }

    virtual void draw() override
    {

        std::pair<color, color> colors;

        if (focused_)
            colors = {color::black, color::white};
        else
            colors = {color::white, color::black};

        std::wstring to_print;
        if (!is_password_)
            to_print = text_;
        else
            to_print = std::wstring(text_.size(), '*');

        this->ui_context_.buffer().text(this->get_attributes().get_x(), this->get_attributes().get_y(), to_print,
                                        colors);
        this->ui_context_.buffer().text(this->get_attributes().get_x() + text_.size(), this->get_attributes().get_y(),
                                        std::wstring(size_ - text_.size(), '_'), colors);
    }

    void clear_on_hide(bool clear_on_hide)
    {
        clear_on_hide_ = clear_on_hide;
    }

    void on_hide() override
    {
        if (clear_on_hide_)
            text_.clear();
    }

    std::wstring const &text() const
    {
        return text_;
    }
};

}   // namespace ui
}   // namespace neo
