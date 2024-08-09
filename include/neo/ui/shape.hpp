#ifndef NEO_UI_SHAPE
#define NEO_UI_SHAPE

#include "neo/ui/attributes.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class CONTEXT>
class shape : public object<CONTEXT>
{
   public:
    using parent_type = object<CONTEXT>;
    using typename parent_type::context_type;

   public:
    shape(typename parent_type::context_type &ui_context, attributes<context_type> const &attrs)
        : object<CONTEXT>(ui_context, attrs)
    {}

    virtual void update(bool is_focused) override
    {}

    virtual void draw(typename CONTEXT::buffer_type &buffer)
    {
        buffer.box(this->get_attributes().get_x(), this->get_attributes().get_y(), this->get_attributes().get_width(),
                   this->get_attributes().get_height());
    }
};

}   // namespace ui
}   // namespace neo

#endif
