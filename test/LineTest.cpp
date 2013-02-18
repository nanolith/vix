#include <gtest/gtest.h>
#include <vix/Line.h>

using namespace std;
using namespace vix;

TEST(Line, defaultConstructor)
{
    Line l;

    ASSERT_EQ(l.str(), L"");
}

TEST(Line, stringConstructor)
{
    wstring s(L"This is a test");
    Line l(s);

    ASSERT_EQ(l.str(), s);
}

TEST(Line, copyConstructor)
{
    Line ol(L"Test");
    Line l(ol);

    ASSERT_EQ(l.str(), ol.str());
}

TEST(Line, assignmentOperator)
{
    Line l1(L"Test1");
    Line l2(L"Test2");

    Line l(l1);
    l = l2;

    ASSERT_EQ(l.str(), l2.str());
}

TEST(Line, strGet)
{
    wstring foo(L"foo");
    Line l(L"foo");

    ASSERT_EQ(l.str(), foo);
}

TEST(Line, strSet)
{
    wstring foo(L"foo");
    Line l;

    l.str(foo);

    ASSERT_EQ(l.str(), foo);
}
