#include <gtest/gtest.h>
#include <vix/Buffer.h>
#include <vix/Line.h>

using namespace vix;

TEST(Buffer, defaultConstructor)
{
    Buffer b;

    ASSERT_EQ(b.lines(), 0);
    ASSERT_EQ(b.begin(), b.end());
    ASSERT_EQ(b.rbegin(), b.rend());
}

TEST(Buffer, globalInsert)
{
    Buffer b;
    Line firstLine(L"First Line");
    Line secondLine(L"Second Line");

    ASSERT_EQ(b.lines(), 0);
    b.insert(firstLine);
    ASSERT_EQ(b.lines(), 1);
    b.insert(secondLine);
    ASSERT_EQ(b.lines(), 2);

    //now, secondLine should be before firstLine
    Buffer::iterator i = b.begin();
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i->str(), firstLine.str());
}
