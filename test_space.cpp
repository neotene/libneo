#include <gtest/gtest.h>
#include <neo/dim2/space.hpp>

TEST(space, construct)
{
    neo::dim2::space<int, 10, 10> s;
    ASSERT_EQ(s.get_width(), 10);
    ASSERT_EQ(s.get_height(), 10);
}

TEST(space, access)
{
    neo::dim2::space<int, 10, 10> s;
    s(0, 0) = 1;
    ASSERT_EQ(s(0, 0), 1);

    s(9, 9) = 2;
    ASSERT_EQ(s(9, 9), 2);

    s(5, 5) = 3;
    ASSERT_EQ(s(5, 5), 3);

    s(5, 5) = 4;
    ASSERT_EQ(s(5, 5), 4);

    ASSERT_ANY_THROW(s(10, 10) = 5);
}

TEST(composite_space, construct)
{
    neo::dim2::composite_space<neo::dim2::space<int, 10, 10>> cs;
    ASSERT_EQ(cs(0, 0).get_width(), 10);
    ASSERT_EQ(cs(0, 0).get_height(), 10);
}

TEST(composite_space, access)
{
    neo::dim2::composite_space<neo::dim2::space<int, 10, 10>> cs;
    cs(0, 0)(0, 0) = 1;
    ASSERT_EQ(cs(0, 0)(0, 0), 1);

    cs(9, 9)(9, 9) = 2;
    ASSERT_EQ(cs(9, 9)(9, 9), 2);

    cs(5, 5)(5, 5) = 3;
    ASSERT_EQ(cs(5, 5)(5, 5), 3);

    cs(5, 5)(5, 5) = 4;
    ASSERT_EQ(cs(5, 5)(5, 5), 4);

    ASSERT_ANY_THROW(cs(10, 10)(10, 10) = 5);
}

TEST(view, construct)
{
    using space_type = neo::dim2::space<int, 10, 10>;
    neo::dim2::composite_space<space_type> cs;
    neo::dim2::view<neo::dim2::composite_space<space_type>> v(cs);
}

TEST(view, access)
{
    using space_type = neo::dim2::space<int, 10, 10>;
    using composite_space_type = neo::dim2::composite_space<space_type>;
    using view_type = composite_space_type::view_type;

    composite_space_type cs;
    view_type v = cs.get_view();

    ASSERT_EQ(cs.total_size(), 0);

    cs(0, 0)(0, 0) = 1;
    ASSERT_EQ(v(0, 0), 1);

    ASSERT_EQ(cs.total_size(), space_type::width * space_type::height);

    view_type::coord_type space_x = 9;
    view_type::coord_type space_y = 9;

    space_type::coord_type cell_x = 9;
    space_type::coord_type cell_y = 9;

    ASSERT_NO_THROW(v(space_x * space_type::width + cell_x, space_y * space_type::height + cell_y) = 2);

    ASSERT_EQ(cs.total_size(), 2 * (space_type::width * space_type::height));

    ASSERT_EQ(v(space_x * space_type::width + cell_x, space_y * space_type::height + cell_y), 2);

    ASSERT_EQ(cs(space_x, space_y)(cell_x, cell_y), 2);
}

TEST(view, translate)
{
    using space_type = neo::dim2::space<int, 1, 1>;
    using composite_space_type = neo::dim2::composite_space<space_type>;
    using view_type = composite_space_type::view_type;

    composite_space_type cs;

    view_type v = cs.get_view();

    v(0, 0) = 1;

    ASSERT_EQ(v(0, 0), 1);

    ASSERT_EQ(cs.total_size(), space_type::width * space_type::height);

    v(1, 0) = 2;

    ASSERT_EQ(v(0, 0), 1);

    v.translate(1, 0);

    ASSERT_EQ(v(0, 0), 2);

    v.translate(-1, 0);

    ASSERT_EQ(v(0, 0), 1);
}
