#ifndef NEO_UI_CONTEXT
#define NEO_UI_CONTEXT

#include <vector>

#include "neo/ui/frame.hpp"
#include "neo/ui/input.hpp"

namespace neo {
namespace ui {

template <class BUFFER>
class context
{
   public:
    using buffer_type = BUFFER;
    using window_type = frame<context<BUFFER>>;
    using window_container_type = std::vector<window_type *>;
    using object_iterator_container_type = std::vector<typename window_type::frame_container_type::iterator>;

   protected:
    window_container_type objects_;
    object_iterator_container_type iterators_;
    buffer_type buffer_;
    input_manager input_manager_;

   public:
    virtual ~context()
    {}

    virtual size_t width() const = 0;
    virtual size_t height() const = 0;
    virtual void refresh() = 0;

    virtual input read() = 0;

    buffer_type &buffer()
    {
        return buffer_;
    }

    void run()
    {
        for (; !objects_.empty();)
        {
            refresh();

            input input = input_manager_.get();

            if (input.special(input::special_key::escape))
            {
                pop_window();
                continue;
            }
            // // if (input.special(input::special_key::tab))
            // if (map.GetBoolWasDown(key::tab))
            // {
            //     typename window_type::frame_container_type::iterator new_focus;
            //     if (!input.special(input::special_key::shift_tab))
            //         new_focus = objects_.back()->first_focusable(iterators_.back());
            //     else
            //         new_focus = objects_.back()->first_focusable(iterators_.back(), true);

            //     (*iterators_.back())->focus_change(false);
            //     (*new_focus)->focus_change(true);
            //     iterators_.back() = new_focus;
            // }

            // (*iterators_.back())->input(input);
        }
    }

    template <class CONTEXT>
    void push_window(frame<CONTEXT> &frame)
    {
        objects_.push_back(reinterpret_cast<window_type *>(&frame));
        iterators_.push_back(objects_.back()->first_focusable());
        for (typename window_type::frame_container_type::value_type obj : objects_.back()->children()) obj->on_show();
        (*iterators_.back())->focus_change(true);
    }

    void pop_window()
    {
        for (typename window_type::frame_container_type::value_type obj : objects_.back()->children()) obj->on_hide();
        objects_.pop_back();
        (*iterators_.back())->focus_change(false);
        iterators_.pop_back();
    }

    void pop_all_windows()
    {
        objects_.clear();
        iterators_.clear();
    }
};

}   // namespace ui
}   // namespace neo

#endif
