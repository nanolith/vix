#include <vix/Buffer.h>

using namespace vix;

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

Buffer::iterator
Buffer::begin()
{
    return lines_.begin();
}

Buffer::iterator
Buffer::end()
{
    return lines_.end();
}

Buffer::const_iterator
Buffer::begin() const
{
    return lines_.begin();
}

Buffer::const_iterator
Buffer::end() const
{
    return lines_.end();
}

Buffer::reverse_iterator
Buffer::rbegin()
{
    return lines_.rbegin();
}

Buffer::reverse_iterator
Buffer::rend()
{
    return lines_.rend();
}

void
Buffer::insert(const Line& newLine)
{
    lines_.push_front(newLine);
}

void
Buffer::append(const Line& newLine)
{
    lines_.push_back(newLine);
}

void
Buffer::insert(const Buffer::iterator& before, const Line& newLine)
{
    lines_.insert(before, newLine);
}

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

void
Buffer::erase(const Buffer::iterator& line)
{
    lines_.erase(line);
}

size_t
Buffer::lines() const
{
    return lines_.size();
}
