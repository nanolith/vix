#ifndef  VIX_SERIALIZABLE_HEADER_GUARD
# define VIX_SERIALIZABLE_HEADER_GUARD

#include <iosfwd>
#include <vix/SerialException.h>

namespace vix
{
    /**
     * The Serializable interface provides two methods: serialRead and
     * serialWrite.  The serialRead method reads object state from a binary
     * istream.  The serialWrite method reads object state from a binary
     * ostream.  How this data is serialized is up to the implementing class.
     */
    class Serializable : virtual public Serializable
    {
    public:

        /**
         * Read data from a binary input stream and update object state.
         *
         * \throw vix::exception::SerialRead if serialization fails.
         */
        virtual void serialRead(std::istream& in) = 0;

        /**
         * Write data to a binary input stream based on object state.
         *
         * \throw vix::exception::SerialWrite if serialization fails.
         */
        virtual void serialWrite(std::ostream& out) const = 0;
    };
}

#endif //VIX_SERIALIZABLE_HEADER_GUARD
