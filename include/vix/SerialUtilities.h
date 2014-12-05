#ifndef  VIX_SERIAL_UTILITIES_HEADER_GUARD
# define VIX_SERIAL_UTILITIES_HEADER_GUARD

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <vix/SerialException.h>

/**
 * The SerialUtilities header file provides some utility functions for
 * serializing primitive types to a binary stream.
 */
namespace vix
{
    /**
     * serialWriteFixedBuffer writes a fixed size buffer to the provided binary
     * stream.  This function does not write any size information to the stream;
     * it is assumed that the buffer size is fixed.
     *
     * \param out           The stream to which the buffer is written.
     * \param buffer        The buffer to be written.
     * \param size          The size of the buffer to be written.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWriteFixedBuffer(std::ostream& out, const void* buffer, std::size_t size);

    /**
     * serialReadFixedBuffer reads a fixed size buffer from the provided binary
     * input stream.  This function does not read any size information from the
     * stream; it is assumed that the buffer size is fixed.
     *
     * \param in            The stream from which the buffer is read.
     * \param buffer        Pointer to the output buffer from the read.
     * \param size          The size of the buffer to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialReadFixedBuffer(std::istream& in, void* buffer, std::size_t size);

    /**
     * serialWriteBuffer writes a variable size buffer to the provided binary
     * stream.  This function takes an optional parameter to control how many
     * bytes of size data is written.  The size data is written first, followed
     * by the buffer.  By default, the size data is 16-bit, which provides for a
     * 64 kilobyte buffer.
     *
     * \param out           The input stream.
     * \param buffer        The pointer to the buffer.
     * \param size          The number of bytes to write.
     * \param sizeBytes     The number of bytes to write for the size, up to 4.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWriteBuffer(std::ostream& out, const void* buffer, std::size_t size, std::size_t sizeBytes = 2);

    /**
     * serialReadBuffer reads a variable size buffer from the provided binary
     * stream.  This function takes an optional parameter to control how many
     * bytes of size data is read.  The size data is read first, followed
     * by the buffer.  By default, the size data is 16-bit, which provides for a
     * 64 kilobyte buffer.
     *
     * \param in            The input stream.
     * \param buffer        The pointer to the buffer.
     * \param size          On input, the max size of the buffer.  On output,
     *                      the number of bytes read.
     * \param sizeBytes     The number of bytes to read for the size, up to 4.
     *
     * \throw vix::exception::SerialRead if the serial read fails, or if the
     *        data read was truncated.
     */
    void serialReadBuffer(std::ostream& in, void* buffer, std::size_t& size, std::size_t sizeBytes = 2);

    /**
     * serialWrite(uint64_t) is an overloaded function that writes an unsigned
     * 64-bit value to the output stream.  This value is written in Big Endian
     * format for portability purposes.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The unsigned 64-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::uint64_t value);

    /**
     * serialWrite(uint32_t) is an overloaded function that writes an unsigned
     * 32-bit value to the output stream.  This value is written in Big Endian
     * format for portability purposes.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The unsigned 32-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::uint32_t value);

    /**
     * serialWrite(uint16_t) is an overloaded function that writes an unsigned
     * 16-bit value to the output stream.  This value is written in Big Endian
     * format for portability purposes.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The unsigned 16-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::uint16_t value);

    /**
     * serialWrite(uint8_t) is an overloaded function that writes an unsigned
     * 8-bit value to the output stream.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The unsigned 8-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::uint8_t value);

    /**
     * serialWrite(int64_t) is an overloaded function that writes a signed
     * 64-bit value to the output stream.  This value is written in Big Endian
     * format for portability purposes.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The signed 64-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::int64_t value);

    /**
     * serialWrite(int32_t) is an overloaded function that writes a signed
     * 32-bit value to the output stream.  This value is written in Big Endian
     * format for portability purposes.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The signed 32-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::int32_t value);

    /**
     * serialWrite(int16_t) is an overloaded function that writes a signed
     * 16-bit value to the output stream.  This value is written in Big Endian
     * format for portability purposes.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The signed 16-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::int16_t value);

    /**
     * serialWrite(int8_t) is an overloaded function that writes a signed
     * 8-bit value to the output stream.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The signed 8-bit value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, std::int8_t value);

    /**
     * serialRead(uint64_t) is an overloaded function that reads an unsigned
     * 64-bit value from the input stream.  This value is read in Big Endian
     * format for portability purposes.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The unsigned 64-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::uint64_t& value);

    /**
     * serialRead(uint32_t) is an overloaded function that reads an unsigned
     * 32-bit value from the input stream.  This value is read in Big Endian
     * format for portability purposes.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The unsigned 32-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::uint32_t& value);

    /**
     * serialRead(uint16_t) is an overloaded function that reads an unsigned
     * 16-bit value from the input stream.  This value is read in Big Endian
     * format for portability purposes.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The unsigned 16-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::uint16_t& value);

    /**
     * serialRead(uint8_t) is an overloaded function that reads an unsigned
     * 8-bit value from the input stream.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The unsigned 8-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::uint8_t& value);

    /**
     * serialRead(int64_t) is an overloaded function that reads a signed
     * 64-bit value from the input stream.  This value is read in Big Endian
     * format for portability purposes.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The signed 64-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::int64_t& value);

    /**
     * serialRead(int32_t) is an overloaded function that reads a signed
     * 32-bit value from the input stream.  This value is read in Big Endian
     * format for portability purposes.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The signed 32-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::int32_t& value);

    /**
     * serialRead(int16_t) is an overloaded function that reads a signed
     * 16-bit value from the input stream.  This value is read in Big Endian
     * format for portability purposes.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The signed 16-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::int16_t& value);

    /**
     * serialRead(int8_t) is an overloaded function that reads a signed
     * 8-bit value from the input stream.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The signed 8-bit value to be read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::int8_t& value);

    /**
     * serialWrite(const std::string&) is an overloaded function that writes a
     * string to the output stream as a variable buffer.
     *
     * \param out           The output stream to which this value is written.
     * \param value         The string value to write.
     *
     * \throw vix::exception::SerialWrite if the serial write fails.
     */
    void serialWrite(std::ostream& out, const std::string& value);

    /**
     * serialRead(std::string&) is an overloaded function that reads a
     * string from the input stream as a variable buffer.
     *
     * \param in            The input stream from which this value is read.
     * \param value         The string value to read.
     *
     * \throw vix::exception::SerialRead if the serial read fails.
     */
    void serialRead(std::istream& in, std::string& value);
}

#endif //VIX_SERIAL_UTILITIES_HEADER_GUARD
