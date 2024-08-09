#ifndef NEO_UI_CONTEXT
#define NEO_UI_CONTEXT

#include <vector>

#include "neo/ui/input.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class IMPL>
class context
{
   public:
    using object_type = object<IMPL>;
    using layer_type = std::vector<object_type *>;
    using stack_type = std::vector<layer_type>;

   protected:
    std::vector<std::pair<bool, typename layer_type::iterator>> iterators_;
    stack_type stack_;

   public:
    context()
    {
        push_new_layer();
    }

    virtual ~context()
    {}

    virtual size_t width() const = 0;
    virtual size_t height() const = 0;
    virtual void refresh() = 0;

    virtual input read() = 0;

    template <class CONTEXT>
    void add_object_to_current_layer(ui::object<CONTEXT> *ui_object)
    {
        stack_.back().push_back(ui_object);
        if (iterators_.back().first == true)
        {
            iterators_.back().first = false;
        }

        iterators_.back().second = stack_.back().begin();
    }

    void push_new_layer()
    {
        stack_.push_back(layer_type());
        iterators_.push_back({true, layer_type::iterator()});
    }

    void pop_top_layer()
    {
        stack_.pop_back();
        iterators_.pop_back();
    }

    void run()
    {
        for (; !stack_.empty();)
        {
            refresh();

            input input = read();

            if (input.special(input::special_key::escape))
            {
                pop_top_layer();
                continue;
            } else if (input.special(input::special_key::tab))
            {
                bool backward = false;
                if (input.special(input::special_key::shift))
                    backward = true;

                auto pair = iterators_.back();
                auto it = pair.second;
                auto prev = it;

                if (!backward)
                {
                    ++it;
                    if (it == stack_.back().end())
                        it = stack_.back().begin();
                } else
                {
                    if (it == stack_.back().begin())
                        it = stack_.back().end() - 1;
                    else
                        --it;
                }

                (*prev)->update_focus(false);
                (*it)->update_focus(true);
                iterators_.back().second = it;
            } else
            {
                if (!iterators_.back().first)
                    (*iterators_.back().second)->on_input(input);
            }
        }
    }
};

}   // namespace ui
}   // namespace neo

#endif
