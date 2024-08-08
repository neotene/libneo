#ifndef NEO_UI_LABEL
#define NEO_UI_LABEL

#include <string>

#include "neo/ui/attributes.hpp"
#include "neo/ui/color.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class Context>
class label : public object<Context>
{
   public:
    using parent_type = object<Context>;
    using dimension_type = typename parent_type::context_type::buffer_type::size_type;
    using coord_type = typename parent_type::coord_type;
    using typename parent_type::context_type;

   private:
    std::wstring text_;
    color fg_;
    color bg_;

   public:
    label(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs,
          std::wstring const &text, frame<Context> *parent = nullptr)
        : parent_type(ui_context, attrs), text_(text), fg_(color::white), bg_(color::black)
    {
        if (!parent)
            return;
        parent->add_child(this);
    }

   public:
    unsigned int size() const
    {
        return text_.size();
    }

    virtual void draw() override
    {
        this->ui_context_.buffer().text(this->get_attributes().get_x(), this->get_attributes().get_y(), text_,
                                        {fg_, bg_});
    }

    void text(std::wstring const &text)
    {
        text_ = text;
    }

    void set_color(color const &fg, color const &bg)
    {
        fg_ = fg;
        bg_ = bg;
    }
};

}   // namespace ui
}   // namespace neo

#endif
