#include <gtest/gtest.h>
#include <vix/Buffer.h>
#include <vix/Line.h>

#include <memory>

using namespace vix;

class BufferTest : public ::testing::Test
{
protected:
    Buffer b;
    Line firstLine;
    Line secondLine;
    Line thirdLine;
    Line fourthLine;

    Buffer::iterator i;
    Buffer::const_iterator ci;

    virtual void SetUp() {
        b.clear();
        firstLine = Line(L"First Line");
        secondLine = Line(L"Second Line");
        thirdLine = Line(L"Third Line");
        fourthLine = Line(L"Fourth Line");
    }
};

TEST_F(BufferTest, defaultConstructor)
{
    ASSERT_EQ(b.lines(), 0);
    ASSERT_EQ(b.begin(), b.end());
    ASSERT_EQ(b.rbegin(), b.rend());
}

TEST_F(BufferTest, globalInsert)
{
    ASSERT_EQ(b.lines(), 0);
    b.insert(firstLine);
    ASSERT_EQ(b.lines(), 1);
    b.insert(secondLine);
    ASSERT_EQ(b.lines(), 2);

    //now, secondLine should be before firstLine
    i = b.begin();
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

TEST_F(BufferTest, constantIteration)
{
    b.insert(secondLine);
    b.insert(firstLine);

    const Buffer& cb = b;
    ASSERT_NE(cb.begin(), cb.end());
    ci = cb.begin();
    ASSERT_EQ(ci->str(), firstLine.str());
    ++ci;
    ASSERT_EQ(ci->str(), secondLine.str());
    ++ci;
    ASSERT_EQ(ci, b.end());
}

TEST_F(BufferTest, append)
{
    b.append(firstLine);
    b.append(secondLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

TEST_F(BufferTest, insertBefore)
{
    b.append(firstLine);
    b.append(thirdLine);

    //get to the second line (thirdLine)
    i = b.begin();
    ++i;

    //insert should insert before a given line
    b.insert(i, secondLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i->str(), thirdLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

TEST_F(BufferTest, erase)
{
    b.append(firstLine);
    b.append(secondLine);

    //erase the first line
    b.erase(b.begin());

    i = b.begin();
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

TEST_F(BufferTest, appendAfter)
{
    b.append(firstLine);
    b.append(thirdLine);

    //append secondLine after firstLine
    b.append(b.begin(), secondLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i->str(), thirdLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

TEST_F(BufferTest, appendAfterEnd)
{
    b.append(firstLine);

    //append secondLine after firstLine
    b.append(b.begin(), secondLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

TEST_F(BufferTest, appendAfterEmpty)
{
    b.append(b.begin(), firstLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}
