#ifndef  VIX_CURSOR_HEADER_GUARD
# define VIX_CURSOR_HEADER_GUARD

namespace vix
{
    class Cursor
    {
    public:

        ///Default constructor
        Cursor(int x = 0, int y = 0);

        ///Copy constructor
        Cursor(const Cursor& c);

        ///x getter
        int x() const;

        ///x setter
        void x(int x);

        ///y getter
        int y() const;

        ///y setter
        void y(int y);

    private:
        int x_;
        int y_;
    };
}

#endif //VIX_CURSOR_HEADER_GUARD
