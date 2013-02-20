#ifndef  VIX_BUFFER_HEADER_GUARD
# define VIX_BUFFER_HEADER_GUARD

#include <list>
#include <vix/Line.h>

namespace vix
{
    /**
     * This class represents a physical buffer in memory.
     */
    class Buffer
    {
        typedef
        std::list<Line>
        LineList;

    public:

        /**
         * The iterator type for this buffer.
         */
        typedef
        LineList::iterator
        iterator;

        /**
         * The const_iterator type for this buffer.
         */
        typedef
        LineList::const_iterator
        const_iterator;

        /**
         * The reverse_iterator type for this buffer.
         */
        typedef
        LineList::reverse_iterator
        reverse_iterator;

        /**
         * The const_reverse_iterator type for this buffer.
         */
        typedef
        LineList::const_reverse_iterator
        const_reverse_iterator;

        /**
         * Default constructor.  Create an empty buffer.
         */
        Buffer();

        /**
         * Destructor.
         */
        ~Buffer();

        /*** Iteration functions ***/

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        reverse_iterator rbegin();
        reverse_iterator rend();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;

        /**
         * Insert a line into the beginning of the buffer.
         */
        void insert(const Line& newLine);

        /**
         * Insert a line before the given iterator.
         */
        void insert(const iterator& before, const Line& newLine);

        /**
         * Append a new life after the given iterator.
         */
        void append(const iterator& after, const Line& newLine);

        /**
         * Append a line to the end of the buffer.
         */
        void append(const Line& newLine);

        /**
         * Erase a line.
         */
        void erase(const iterator& line);
         
        /**
         * Clear the buffer.
         */
        void clear();

        /**
         * Returns the number of lines in this buffer.
         */
        size_t lines() const;

    private:
        LineList lines_;
    };
}

#endif //VIX_BUFFER_HEADER_GUARD
