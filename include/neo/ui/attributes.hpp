#pragma once

// #include <neo/ui/object.hpp>
// #include <neo/ui/frame.hpp>

namespace neo {
namespace ui {

template <class Context>
class frame;

template <class Context>
class object;

enum class anchor
{
    // none,
    top_left,
    top_center,
    top_right,
    center_left,
    center,
    center_right,
    bottom_left,
    bottom_center,
    bottom_right
};

template <class Context>
class attributes
{
  public:
    using context_type = Context;
    using size_type = typename Context::buffer_type::size_type;

  private:
    size_type x_;
    size_type y_;
    size_type width_;
    size_type height_;
    attributes<context_type> const *relative_;
    anchor self_anchor_;
    anchor relative_anchor_;

  public:
    attributes(size_type const &x, size_type const &y)
        : x_(x)
        , y_(y)
        , width_(0)
        , height_(0)
        , relative_(nullptr)
        , self_anchor_(anchor::center)
        , relative_anchor_(anchor::center)
    {}

    attributes(size_type const &x, size_type const &y, size_type const &width, size_type const &height)
        : x_(x)
        , y_(y)
        , width_(width)
        , height_(height)
        , relative_(nullptr)
        , self_anchor_(anchor::center)
        , relative_anchor_(anchor::center)
    {}

    attributes(size_type const &x, size_type const &y, size_type const &width, size_type const &height,
               attributes<context_type> const *relative, anchor const &self_anchor, anchor const &relative_anchor)
        : x_(x)
        , y_(y)
        , width_(width)
        , height_(height)
        , relative_(relative)
        , self_anchor_(self_anchor)
        , relative_anchor_(relative_anchor)
    {}

    attributes(size_type const &x, size_type const &y, attributes<context_type> const *relative,
               anchor const &relative_anchor)
        : x_(x)
        , y_(y)
        , width_(0)
        , height_(0)
        , relative_(relative)
        , self_anchor_(anchor::center)
        , relative_anchor_(relative_anchor)
    {}

  public:
    size_type get_width() const
    {
        return width_;
    }

    size_type get_height() const
    {
        return height_;
    }

    size_type get_x() const
    {
        if (relative_)
        {
            size_type x = x_;
            switch (self_anchor_)
            {
            case anchor::top_center:
            case anchor::center:
            case anchor::bottom_center:
                x -= width_ / 2;
                break;
            case anchor::top_right:
            case anchor::center_right:
            case anchor::bottom_right:
                x -= width_;
                break;
            default:
                break;
            }
            switch (relative_anchor_)
            {
            case anchor::top_left:
            case anchor::center_left:
            case anchor::bottom_left:
                return relative_->get_x() + x;
            case anchor::top_center:
            case anchor::center:
            case anchor::bottom_center:
                return relative_->get_x() + relative_->get_width() / 2 + x;
            case anchor::top_right:
            case anchor::center_right:
            case anchor::bottom_right:
                return relative_->get_x() + relative_->get_width() + x;
            default:
                break;
            }
        }
        return x_;
    }

    size_type get_y() const
    {
        if (relative_)
        {
            size_type y = y_;
            switch (self_anchor_)
            {
            case anchor::center_left:
            case anchor::center:
            case anchor::center_right:
                y -= height_ / 2;
                break;
            case anchor::bottom_left:
            case anchor::bottom_center:
            case anchor::bottom_right:
                y -= height_;
                break;
            default:
                break;
            }
            switch (relative_anchor_)
            {
            case anchor::top_left:
            case anchor::top_center:
            case anchor::top_right:
                return relative_->get_y() + y;
            case anchor::center_left:
            case anchor::center:
            case anchor::center_right:
                return relative_->get_y() + relative_->get_height() / 2 + y;
            case anchor::bottom_left:
            case anchor::bottom_center:
            case anchor::bottom_right:
                return relative_->get_y() + relative_->get_height() + y;
            default:
                break;
            }
        }
        return y_;
    }
};

}   // namespace ui
}   // namespace neo
