#ifndef NEO_UI_FRAME
#define NEO_UI_FRAME

#include <stdexcept>
#include <vector>

#include "neo/ui/attributes.hpp"
#include "neo/ui/object.hpp"

namespace neo {
namespace ui {

template <class CONTEXT>
class frame : public object<CONTEXT>
{
   public:
    using parent_type = object<CONTEXT>;
    using dimension_type = typename parent_type::context_type::buffer_type::size_type;
    using coord_type = typename parent_type::coord_type;
    using frame_container_type = std::vector<object<CONTEXT> *>;
    using typename parent_type::context_type;

   private:
    frame_container_type children_;

   public:
    frame(context_type &ui_context, attributes<context_type> const &attrs, frame *parent = nullptr)
        : parent_type(ui_context, attrs)
    {
        ui_context.push(this);
        if (!parent)
            return;
        parent->add_child(this);
    }

    virtual void draw() override
    {
        this->ui_context_.buffer().fill_area(this->get_attributes().get_x(), this->get_attributes().get_y(),
                                             this->get_attributes().get_width(), this->get_attributes().get_height());
        for (auto *child : children_)
            child->draw();
        // this->ui_context_.buffer().box(this->get_attributes().get_x(),
        // this->get_attributes().get_y(),
        //                                this->get_attributes().get_width(),
        //                                this->get_attributes().get_height());
    }

    frame_container_type const &children() const
    {
        return children_;
    }

    frame_container_type &children()
    {
        return children_;
    }

    void add_child(object<CONTEXT> *ui_object)
    {
        children_.emplace_back(ui_object);
    }

    typename frame_container_type::iterator first_focusable(typename frame_container_type::iterator it,
                                                            bool backward = false)
    {
        if (children_.empty())
            throw std::runtime_error("No child in frame");

        auto prev = it;
        do
        {
            if (it == children_.end() - 1 && !backward)
                it = children_.begin();
            else if (it == children_.begin() && backward)
                it = children_.end() - 1;
            else
                backward ? --it : ++it;

            if ((*it)->focusable())
                break;
        } while (it != prev);

        if (it == prev && !(*it)->focusable())
            throw std::runtime_error("No focusable found in frame");

        return it;
    }

    typename frame_container_type::iterator first_focusable()
    {
        return first_focusable(children_.begin());
    }
};

}   // namespace ui
}   // namespace neo

#endif
