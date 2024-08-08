#ifndef NEO_UI_SHAPE
#define NEO_UI_SHAPE

#include "neo/ui/attributes.hpp"
#include "neo/ui/frame.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class Context>
class shape : public object<Context>
{
   public:
    using parent_type = object<Context>;
    using dimension_type = typename parent_type::context_type::buffer_type::size_type;
    using coord_type = typename parent_type::coord_type;
    using typename parent_type::context_type;

   public:
    shape(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs,
          frame<Context> *parent = nullptr)
        : object<Context>(ui_context, attrs)
    {
        if (!parent)
            return;
        parent->add_child(this);
    }

    virtual void draw() override
    {
        this->ui_context_.buffer().box(this->get_attributes().get_x(), this->get_attributes().get_y(),
                                       this->get_attributes().get_width(), this->get_attributes().get_height());
    }
};

}   // namespace ui
}   // namespace neo

#endif
