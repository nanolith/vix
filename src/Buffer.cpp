#include <vix/Buffer.h>

using namespace vix;

/**
 * Default constructor.  Create an empty buffer.
 */
Buffer::Buffer()
{
}

/**
 * Destructor.
 */
Buffer::~Buffer()
{
}

/**
 * Return the begin iterator of the buffer.
 */
Buffer::iterator
Buffer::begin()
{
    return lines_.begin();
}

/**
 * Return the end iterator of the buffer.
 */
Buffer::iterator
Buffer::end()
{
    return lines_.end();
}

/**
 * Return the begin iterator of the buffer. (constant)
 */
Buffer::const_iterator
Buffer::begin() const
{
    return lines_.begin();
}

/**
 * Return the end iterator of the buffer. (constant)
 */
Buffer::const_iterator
Buffer::end() const
{
    return lines_.end();
}

/**
 * Return the begin reverse iterator of the buffer.
 */
Buffer::reverse_iterator
Buffer::rbegin()
{
    return lines_.rbegin();
}

/**
 * Return the end reverse iterator of the buffer.
 */
Buffer::reverse_iterator
Buffer::rend()
{
    return lines_.rend();
}

/**
 * Return the begin reverse iterator of the buffer. (constant)
 */
Buffer::const_reverse_iterator
Buffer::rbegin() const
{
    return lines_.rbegin();
}

/**
 * Return the end reverse iterator of the buffer. (constant)
 */
Buffer::const_reverse_iterator
Buffer::rend() const
{
    return lines_.rend();
}

/**
 * Insert a line into the beginning of the buffer.
 */
void
Buffer::insert(const Line& newLine)
{
    lines_.push_front(newLine);
}

/**
 * Append a line to the end of the buffer.
 */
void
Buffer::append(const Line& newLine)
{
    lines_.push_back(newLine);
}

/**
 * Insert a line before the given iterator.
 */
void
Buffer::insert(const Buffer::iterator& before, const Line& newLine)
{
    lines_.insert(before, newLine);
}

/**
 * Append a new life after the given iterator.
 */
void
Buffer::append(const Buffer::iterator& after, const Line& newLine)
{
    Buffer::iterator position = after;

    if (after == lines_.end() || (++position) == lines_.end())
    {
        lines_.push_back(newLine);
    }
    else
    {
        //note that this insert ONLY occurs if position above is incremented.
        //this hackery with the OR is needed to prevent us from incrementing
        //past the end of the list.
        lines_.insert(position, newLine);
    }
}

/**
 * Erase a line.
 */
void
Buffer::erase(const Buffer::iterator& line)
{
    lines_.erase(line);
}

/**
 * Clear the buffer.
 */
void
Buffer::clear()
{
    lines_.clear();
}

/**
 * Returns the number of lines in this buffer.
 */
size_t
Buffer::lines() const
{
    return lines_.size();
}
