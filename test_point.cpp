#include <gtest/gtest.h>
#include <neo/neo.hpp>

TEST(point, construct)
{
    neo::dim2::point p(1, 2);
    EXPECT_EQ(p.get_x(), 1);
    EXPECT_EQ(p.get_y(), 2);
}

TEST(point, set)
{
    neo::dim2::point p(1, 2);
    p.set_x(3);
    EXPECT_EQ(p.get_x(), 3);
    p.set_y(4);
    EXPECT_EQ(p.get_y(), 4);
}
