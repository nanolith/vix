#include <vix/Line.h>

using namespace std;
using namespace vix;

Line::Line()
{
}

Line::Line(const wstring& s)
    : str_(s)
{
}

Line::Line(const Line& l)
    : str_(l.str())
{
}

const Line&
Line::operator =(const Line& l)
{
    str(l.str());

    return *this;
}

const wstring&
Line::str() const
{
    return str_;
}

void
Line::str(const wstring& str)
{
    str_ = str;
}
