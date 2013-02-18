#ifndef  VIX_LINE_HEADER_GUARD
# define VIX_LINE_HEADER_GUARD

#include <string>

namespace vix
{
    /**
     * This represents a line in a buffer.  It is currently a simple wrapper
     * around wstring.
     */
    class Line
    {
    public:

        /**
         * Construct an empty line
         */
        Line();

        /**
         * Construct a line with the given string value.
         */
        Line(const std::wstring&);

        /**
         * Copy constructor.
         */
        Line(const Line&);

        /**
         * Assignment operator.
         */
        const Line& operator=(const Line&);

        /**
         * Get the wstring representation of this line.
         */
        const std::wstring& str() const;

        /**
         * Replace the contents of this line with the given wstring.
         */
        void str(const std::wstring& str);

    private:
        std::wstring str_;
    };
}

#endif //VIX_LINE_HEADER_GUARD
