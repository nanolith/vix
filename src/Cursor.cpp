#include <vix/Cursor.h>

using namespace vix;

Cursor::Cursor(int x, int y)
    : x_(x), y_(y)
{
}

Cursor::Cursor(const Cursor& c)
    : Cursor(c.x(), c.y())
{
}

int
Cursor::x() const
{
    return x_;
}

void
Cursor::x(int x)
{
    x_ = x;
}

int
Cursor::y() const
{
    return y_;
}

void
Cursor::y(int y)
{
    y_ = y;
}
