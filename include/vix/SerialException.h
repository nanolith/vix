#ifndef  VIX_SERIAL_EXCEPTION_HEADER_GUARD
# define VIX_SERIAL_EXCEPTION_HEADER_GUARD

#include <exception>
#include <string>
#include <vix/ExceptionSpecification.h>

namespace vix
{
    namespace exception
    {
        /**
         * The Serial exception occurs when any serialization failure occurs.
         */
        EXCEPTION_SPECIFICATION(Serial, std::runtime_error);

        /**
         * The SerialRead exception occurs when reading a serialization stream
         * fails.
         */
        EXCEPTION_SPECIFICATION(SerialRead, Serial);

        /**
         * The SerialWrite exception occurs when writing a serialization stream
         * fails.
         */
        EXCEPTION_SPECIFICATION(SerialWrite, Serial);
    }
}

#endif //VIX_SERIAL_EXCEPTION_HEADER_GUARD
