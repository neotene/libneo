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
    using frame_type = frame<context<BUFFER>>;
    using frame_container_type = std::vector<frame_type *>;
    using frame_iterator_container_type = std::vector<typename frame_type::frame_container_type::iterator>;

   protected:
    frame_container_type frames_stack_;
    frame_iterator_container_type iterators_;
    buffer_type buffer_;

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
        for (; !frames_stack_.empty();)
        {
            refresh();

            input input = read();

            if (input.special(input::special_key::escape))
            {
                pop();
                continue;
            }

            if (input.special(input::special_key::tab))
            {
                bool backward = false;
                if (input.special(input::special_key::shift))
                    backward = true;
                typename frame_type::frame_container_type::iterator start_it = frames_stack_.back()->children().begin();
                typename frame_type::frame_container_type::iterator it =
                    frames_stack_.back()->first_focusable(start_it, backward);
            }
        }
    }

    template <class CONTEXT>
    void push(frame<CONTEXT> *frame)
    {
        frames_stack_.push_back(reinterpret_cast<frame_type *>(&frame));
        iterators_.push_back(frames_stack_.back()->first_focusable());
        for (typename frame_type::frame_container_type::value_type obj : frames_stack_.back()->children())
            obj->on_show();
        (*iterators_.back())->focus_change(true);
    }

    void pop()
    {
        for (typename frame_type::frame_container_type::value_type obj : frames_stack_.back()->children())
            obj->on_hide();
        frames_stack_.pop_back();
        (*iterators_.back())->focus_change(false);
        iterators_.pop_back();
    }

    void pop_all()
    {
        frames_stack_.clear();
        iterators_.clear();
    }
};

}   // namespace ui
}   // namespace neo

#endif
