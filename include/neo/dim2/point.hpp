#ifndef NEO_DIM2_POINT
#define NEO_DIM2_POINT

namespace neo {
namespace dim2 {

class point
{
   public:
    using coord_type = int;

   private:
    int x_;
    int y_;

   public:
    point(coord_type const &x, coord_type const &y) : x_(x), y_(y)
    {}

    coord_type const &get_x() const
    {
        return x_;
    }

    coord_type const &get_y() const
    {
        return y_;
    }

    void set_x(coord_type const &x)
    {
        x_ = x;
    }

    void set_y(coord_type const &y)
    {
        y_ = y;
    }

    bool operator<(point const &other) const
    {
        return x_ < other.x_ || y_ < other.y_;
    }
};

}   // namespace dim2
}   // namespace neo

#endif
