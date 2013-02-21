#include <gtest/gtest.h>
#include <vix/Cursor.h>

using namespace vix;

class CursorTest : public ::testing::Test
{
};

TEST_F(CursorTest, defaultConstructor)
{
    Cursor c;

    ASSERT_EQ(c.x(), 0);
    ASSERT_EQ(c.y(), 0);
}

TEST_F(CursorTest, parameterizedConstructor)
{
    Cursor c1(5);
    ASSERT_EQ(c1.x(), 5);

    Cursor c2(5, 7);
    ASSERT_EQ(c2.x(), 5);
    ASSERT_EQ(c2.y(), 7);
}

TEST_F(CursorTest, copyConstructor)
{
    Cursor c(7, 9);

    Cursor cCopy(c);

    ASSERT_EQ(cCopy.x(), c.x());
    ASSERT_EQ(cCopy.y(), c.y());
}

TEST_F(CursorTest, setters)
{
    Cursor c;

    c.x(5);
    ASSERT_EQ(c.x(), 5);

    c.y(5);
    ASSERT_EQ(c.y(), 5);
}
