#ifndef NEO_UI_OBJECT
#define NEO_UI_OBJECT

#include <functional>
#include <map>

#include "neo/ui/attributes.hpp"
#include "neo/uuid.hpp"

namespace neo {
namespace ui {

class input;

template <class CONTEXT>
class object
{
   public:
    using context_type = CONTEXT;
    // using size_type = typename context_type::buffer_type::size_type;
    // using coord_type = size_type;
    using focus_change_callback_type = std::function<void(bool)>;
    using input_callback_type = std::function<void(input const &)>;

   protected:
    context_type &ui_context_;
    std::map<uuid_type, focus_change_callback_type> focus_change_callbacks_;
    std::map<uuid_type, input_callback_type> input_callbacks_;
    attributes<CONTEXT> attributes_;
    bool focusable_;

   public:
    object(context_type &ui_context, attributes<context_type> const &attrs, bool focusable = false)
        : ui_context_(ui_context)
        , attributes_(attrs)
        , focusable_(focusable)
    {
        ui_context.add_object_to_current_layer(this);
    }

    virtual ~object() {};

    virtual void draw(typename CONTEXT::buffer_type &buffer) = 0;

    virtual void update(bool is_focused) = 0;

    attributes<CONTEXT> &get_attributes()
    {
        return attributes_;
    }

    bool focusable() const
    {
        return focusable_;
    }

    attributes<CONTEXT> const &get_attributes() const
    {
        return attributes_;
    }
};

}   // namespace ui
}   // namespace neo

#endif
