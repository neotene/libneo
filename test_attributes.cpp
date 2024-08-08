#include <gtest/gtest.h>

#include <neo/neo.hpp>

#include "neo/term/attributes.hpp"
#include "neo/term/buffer.hpp"
#include "neo/ui/label.hpp"


class test_buffer : public neo::ui::term::buffer
{
   public:
    using size_type = size_t;
};

class test_context
{
   public:
    using buffer_type = test_buffer;

   private:
    buffer_type buffer_;

   public:
    buffer_type &buffer()
    {
        return buffer_;
    }
};

using test_attributes = neo::ui::attributes<test_context>;

TEST(attributes, all)
{
    test_context context;

    test_attributes attrs1(1, 2);

    test_attributes attrs2(0, 0, &attrs1, neo::ui::anchor::top_left);

    ASSERT_EQ(attrs2.get_x(), 1);
    ASSERT_EQ(attrs2.get_y(), 2);

    test_attributes attrs3(0, 0, 3, 4, &attrs2, neo::ui::anchor::center, neo::ui::anchor::top_left);

    // ASSERT_EQ(attrs3.get_x(), 1);
    // ASSERT_EQ(attrs3.get_y(), 2);
}
