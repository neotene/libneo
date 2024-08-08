#ifndef NEO_DIM2_SPACE
#define NEO_DIM2_SPACE

#include <array>
#include <cstdlib>
#include <map>

#include "neo/dim2/point.hpp"

namespace neo {
namespace dim2 {

template <class Cell, unsigned int Width, unsigned int Height>
class space
{
   public:
    using cell_type = Cell;
    using coord_type = unsigned int;

    constexpr static unsigned int width = Width;
    constexpr static unsigned int height = Height;

   private:
    std::array<std::array<Cell, Width>, Height> cells_;

   public:
    cell_type &operator()(coord_type const &x, coord_type const &y)
    {
        return cells_.at(x).at(y);
    }

    cell_type const &operator()(coord_type const &x, coord_type const &y) const
    {
        return cells_.at(x).at(y);
    }

    unsigned int get_width() const noexcept
    {
        return width;
    }

    unsigned int get_height() const noexcept
    {
        return height;
    }
};

template <class CompositeSpace>
class view;

template <class Space>
class composite_space
{
   public:
    using coord_type = int;
    using space_type = Space;
    using view_type = view<composite_space<space_type>>;

   private:
    std::map<point, Space> spaces_;

   public:
    space_type &operator()(coord_type const &x, coord_type const &y)
    {
        return spaces_[point(x, y)];
    }

    space_type const &operator()(coord_type const &x, coord_type const &y) const
    {
        return spaces_.at(point(x, y));
    }

    view_type get_view()
    {
        return view_type(*this);
    }

    constexpr size_t total_size() const
    {
        size_t total_size = 0;
        for (auto const &space : spaces_)
        {
            total_size += space.second.get_width() * space.second.get_height();
        }
        return total_size;
    }
};

template <class CompositeSpace>
class view
{
   public:
    using composite_space_type = CompositeSpace;
    using space_type = typename composite_space_type::space_type;
    using cell_type = typename space_type::cell_type;
    using coord_type = typename composite_space_type::coord_type;

   private:
    constexpr static unsigned int space_width = composite_space_type::space_type::width;
    constexpr static unsigned int space_height = composite_space_type::space_type::height;

   private:
    composite_space_type &composite_space_;
    int x_;
    int y_;

   public:
    view(composite_space_type &composite_space) : composite_space_(composite_space), x_(0), y_(0)
    {}

   public:
    cell_type &operator()(coord_type const &x, coord_type const &y)
    {
        coord_type const offset_x = x_ * space_width;
        coord_type const offset_y = y_ * space_height;

        coord_type const space_x = offset_x + x / space_width;
        coord_type const space_y = offset_y + y / space_height;
        coord_type const cell_x = x % space_width;
        coord_type const cell_y = y % space_height;

        return composite_space_(space_x, space_y)(cell_x, cell_y);
    }

    void translate(int const &x, int const &y)
    {
        x_ += x;
        y_ += y;
    }
};

}   // namespace dim2
}   // namespace neo

#endif