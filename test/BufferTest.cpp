#include <gtest/gtest.h>
#include <vix/Buffer.h>
#include <vix/Line.h>

#include <memory>

#include "BufferChangeObserverMock.h"

using namespace std;
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

/**
 * The default constructor should create an empty buffer.
 */
TEST_F(BufferTest, defaultConstructor)
{
    ASSERT_EQ(b.lines(), 0);
    ASSERT_EQ(b.begin(), b.end());
    ASSERT_EQ(b.rbegin(), b.rend());
}

/**
 * Without a context, insert adds a line to the beginning of a buffer.
 */
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

/**
 * It should be possible to iterate all lines of a constant Buffer.
 */
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

/**
 * Without any context, append adds a line to the end of a Buffer.
 */
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

/**
 * insertBefore adds a line before the given line iterator.
 */
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

/**
 * erase removes the line pointed to by the given iterator from a Buffer.
 */
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

/**
 * replace replaces the given line with the new line.
 */
TEST_F(BufferTest, replace)
{
    b.append(firstLine);
    b.append(secondLine);

    //replace the first line
    b.replace(b.begin(), thirdLine);

    i = b.begin();
    ASSERT_EQ(i->str(), thirdLine.str());
    ++i;
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

/**
 * Attempting to replace the end of the buffer does nothing.
 */
TEST_F(BufferTest, replaceEndFails)
{
    b.append(firstLine);
    b.append(secondLine);

    //replace nothing
    b.replace(b.end(), thirdLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i->str(), secondLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

/**
 * appendAfter appends the given line after the line pointed to by the given
 * iterator.
 */
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

/**
 * Check that appendAfter appends the line after a newly inserted line.
 */
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

/**
 * When the Buffer is empty, appendAfter should work just like append.
 */
TEST_F(BufferTest, appendAfterEmpty)
{
    b.append(b.begin(), firstLine);

    i = b.begin();
    ASSERT_EQ(i->str(), firstLine.str());
    ++i;
    ASSERT_EQ(i, b.end());
}

/**
 * When a line is inserted into a Buffer, all observers are notified that the
 * buffer has changed.
 */
TEST_F(BufferTest, insertNotification)
{
    auto observerMock = make_shared<BufferChangeObserverMock>();

    //add our mock observer.
    b.addObserver(observerMock);

    //at this point, our observer should not have been called.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //insert a line
    b.insert(firstLine);

    //the observer is called with an onBufferChanged event on insert.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //The observer mock should now be clear.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //insert a line before the current line.
    b.insert(b.begin(), secondLine);

    //the observer is called with an onBufferChanged event on insert.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));
}

/**
 * When a line is appended into a Buffer, all observers are notified that the
 * buffer has changed.
 */
TEST_F(BufferTest, appendNotification)
{
    auto observerMock = make_shared<BufferChangeObserverMock>();

    //add our mock observer.
    b.addObserver(observerMock);

    //at this point, our observer should not have been called.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //append a line
    b.append(firstLine);

    //the observer is called with an onBufferChanged event on insert.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //The observer mock should now be clear.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //insert a line before the current line.
    b.append(b.begin(), secondLine);

    //the observer is called with an onBufferChanged event on insert.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));
}

/**
 * When a line is erased from a Buffer, Buffer notifies all observers that it
 * has changed.
 */
TEST_F(BufferTest, eraseNotification)
{
    auto observerMock = make_shared<BufferChangeObserverMock>();

    //append a line
    b.append(firstLine);

    //add our mock observer.
    b.addObserver(observerMock);

    //at this point, our observer should not have been called.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //erase the line
    b.erase(b.begin());

    //the observer is called with an onBufferChanged event on erase.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));
}

/**
 * When a line is replaced in a Buffer, Buffer notifies all observers that it
 * has changed.
 */
TEST_F(BufferTest, replaceNotification)
{
    auto observerMock = make_shared<BufferChangeObserverMock>();

    //append a line
    b.append(firstLine);

    //add our mock observer.
    b.addObserver(observerMock);

    //at this point, our observer should not have been called.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //erase the line
    b.replace(b.begin(), secondLine);

    //the observer is called with an onBufferChanged event on erase.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));
}

/**
 * When a Buffer is cleared, all observers are notified.
 */
TEST_F(BufferTest, clearNotification)
{
    auto observerMock = make_shared<BufferChangeObserverMock>();

    //add our mock observer.
    b.addObserver(observerMock);

    //at this point, our observer should not have been called.
    ASSERT_FALSE(VALIDATE(*observerMock, onBufferChanged).called(&b));

    //clear the buffer
    b.clear();

    //the observer is called with an onBufferChanged event on clear.
    EXPECT_TRUE(VALIDATE(*observerMock, onBufferChanged).called(&b));
}
