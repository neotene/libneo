#pragma once

#include <functional>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include <neo/config.hpp>
#include <neo/ui/ascii.hpp>
#include <neo/ui/attributes.hpp>
#include <neo/ui/print.hpp>
#include <neo/uuid.hpp>

namespace neo {
namespace ui {

class input;

template <class Context>
class object
{
  public:
    using context_type = Context;
    using size_type = typename context_type::buffer_type::size_type;
    using coord_type = size_type;
    using focus_change_callback_type = std::function<void(bool)>;
    using input_callback_type = std::function<void(input const &)>;

  protected:
    context_type &ui_context_;
    std::map<uuid_type, focus_change_callback_type> focus_change_callbacks_;
    std::map<uuid_type, input_callback_type> input_callbacks_;
    attributes<Context> attributes_;
    bool focusable_;

  public:
    object(context_type &ui_context, attributes<context_type> const &attrs, bool focusable = false)
        : ui_context_(ui_context)
        , attributes_(attrs)
        , focusable_(focusable)
    {}

    virtual ~object(){};

    virtual void draw() = 0;

    virtual void
    on_show()
    {}

    virtual void
    on_hide()
    {}

    attributes<Context> &
    get_attributes()
    {
        return attributes_;
    }

    bool
    focusable() const
    {
        return focusable_;
    }

    void
    focus_change(bool focused)
    {
        for (std::pair<uuid_type, focus_change_callback_type> const &func : focus_change_callbacks_)
            func.second(focused);
    }

    void
    input(input const &input)
    {
        for (std::pair<uuid_type, input_callback_type> const &func : input_callbacks_)
            func.second(input);
    }

    attributes<Context> const &
    get_attributes() const
    {
        return attributes_;
    }

  protected:
    uuid_type
    on_focus_change(focus_change_callback_type &&callback)
    {
        uuid_type uuid_key = uuid();
        focus_change_callbacks_[uuid_key] = std::move(callback);
        return uuid_key;
    }

    uuid_type
    on_input(input_callback_type &&callback)
    {
        uuid_type uuid_key = uuid();
        input_callbacks_[uuid_key] = std::move(callback);
        return uuid_key;
    }
};

}   // namespace ui
}   // namespace neo
