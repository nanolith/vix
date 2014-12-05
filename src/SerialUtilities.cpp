#include <cassert>
#include <iostream>
#include <vix/SerialUtilities.h>

using namespace std;
using namespace vix;

namespace {
    const string WRITE_FAILED{"Serial write failed."};
    const string READ_FAILED{"Serial read failed."};
}

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
void
vix::serialWriteFixedBuffer(std::ostream& out, const void* buffer, std::size_t size)
{
    out.write((const char*)buffer, size);

    if (out.bad())
        throw exception::SerialWrite(WRITE_FAILED);
}

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
void
vix::serialReadFixedBuffer(std::istream& in, void* buffer, std::size_t size)
{
    if (in.read((char*)buffer, size).fail())
        throw exception::SerialRead(READ_FAILED);
}

/**
 * Helper function to write a big endian unsigned byte value.
 */
static void
serialWriteBigEndianUnsigned(std::ostream& out, std::uint32_t value, std::size_t sizeBytes)
{
    //we support between 1 and 4 size bytes.
    assert(sizeBytes >= 1 && sizeBytes <= 4);

    switch (sizeBytes)
    {
        case 4:
            serialWrite(out, (uint8_t)((value >> 24) & 0xFF));
            // fall-through

        case 3:
            serialWrite(out, (uint8_t)((value >> 16) & 0xFF));
            // fall-through

        case 2:
            serialWrite(out, (uint8_t)((value >> 8) & 0xFF));
            // fall-through

        case 1:
            serialWrite(out, (uint8_t)((value) & 0xFF));
    }
}

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
void
vix::serialWriteBuffer(std::ostream& out, const void* buffer, std::size_t size, std::size_t sizeBytes)
{
    //write the size bytes
    serialWriteBigEndianUnsigned(out, size, sizeBytes);

    //write the fixed buffer
    serialWriteFixedBuffer(out, buffer, size);
}

/**
 * serialWrite(uint8_t) is an overloaded function that writes an unsigned
 * 8-bit value to the output stream.
 *
 * \param out           The output stream to which this value is written.
 * \param value         The unsigned 8-bit value to write.
 *
 * \throw vix::exception::SerialWrite if the serial write fails.
 */
void
vix::serialWrite(std::ostream& out, std::uint8_t value)
{
    serialWriteFixedBuffer(out, &value, sizeof(value));
}

/**
 * serialRead(uint8_t) is an overloaded function that reads an unsigned
 * 8-bit value from the input stream.
 *
 * \param in            The input stream from which this value is read.
 * \param value         The unsigned 8-bit value to be read.
 *
 * \throw vix::exception::SerialRead if the serial read fails.
 */
void
vix::serialRead(std::istream& in, std::uint8_t& value)
{
    serialReadFixedBuffer(in, &value, sizeof(value));
}

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
void
vix::serialWrite(std::ostream& out, std::uint16_t value)
{
    uint8_t buffer[sizeof(value)];

    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;

    serialWriteFixedBuffer(out, buffer, sizeof(buffer));
}

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
void
vix::serialRead(std::istream& in, std::uint16_t& value)
{
    uint8_t buffer[sizeof(value)];

    serialReadFixedBuffer(in, buffer, sizeof(buffer));

    value  = ((uint16_t)buffer[0]) << 8;
    value |= ((uint16_t)buffer[1]);
}

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
void
vix::serialWrite(std::ostream& out, std::uint32_t value)
{
    uint8_t buffer[sizeof(value)];

    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >>  8) & 0xFF;
    buffer[3] = (value      ) & 0xFF;

    serialWriteFixedBuffer(out, buffer, sizeof(buffer));
}

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
void
vix::serialRead(std::istream& in, std::uint32_t& value)
{
    uint8_t buffer[sizeof(value)];

    serialReadFixedBuffer(in, buffer, sizeof(buffer));

    value  = ((uint32_t)buffer[0]) << 24;
    value |= ((uint32_t)buffer[1]) << 16;
    value |= ((uint32_t)buffer[2]) <<  8;
    value |= ((uint32_t)buffer[3]);
}

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
void
vix::serialWrite(std::ostream& out, std::uint64_t value)
{
    uint8_t buffer[sizeof(value)];

    buffer[0] = (value >> 56) & 0xFF;
    buffer[1] = (value >> 48) & 0xFF;
    buffer[2] = (value >> 40) & 0xFF;
    buffer[3] = (value >> 32) & 0xFF;
    buffer[4] = (value >> 24) & 0xFF;
    buffer[5] = (value >> 16) & 0xFF;
    buffer[6] = (value >>  8) & 0xFF;
    buffer[7] = (value      ) & 0xFF;

    serialWriteFixedBuffer(out, buffer, sizeof(buffer));
}

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
void
vix::serialRead(std::istream& in, std::uint64_t& value)
{
    uint8_t buffer[sizeof(value)];

    serialReadFixedBuffer(in, buffer, sizeof(buffer));

    value  = ((uint64_t)buffer[0]) << 56;
    value |= ((uint64_t)buffer[1]) << 48;
    value |= ((uint64_t)buffer[2]) << 40;
    value |= ((uint64_t)buffer[3]) << 32;
    value |= ((uint64_t)buffer[4]) << 24;
    value |= ((uint64_t)buffer[5]) << 16;
    value |= ((uint64_t)buffer[6]) <<  8;
    value |= ((uint64_t)buffer[7]);
}

/**
 * serialWrite(int8_t) is an overloaded function that writes an unsigned
 * 8-bit value to the output stream.
 *
 * \param out           The output stream to which this value is written.
 * \param value         The unsigned 8-bit value to write.
 *
 * \throw vix::exception::SerialWrite if the serial write fails.
 */
void
vix::serialWrite(std::ostream& out, std::int8_t value)
{
    serialWriteFixedBuffer(out, &value, sizeof(value));
}

/**
 * serialRead(int8_t) is an overloaded function that reads an unsigned
 * 8-bit value from the input stream.
 *
 * \param in            The input stream from which this value is read.
 * \param value         The unsigned 8-bit value to be read.
 *
 * \throw vix::exception::SerialRead if the serial read fails.
 */
void
vix::serialRead(std::istream& in, std::int8_t& value)
{
    serialReadFixedBuffer(in, &value, sizeof(value));
}

/**
 * serialWrite(int16_t) is an overloaded function that writes an unsigned
 * 16-bit value to the output stream.  This value is written in Big Endian
 * format for portability purposes.
 *
 * \param out           The output stream to which this value is written.
 * \param value         The unsigned 16-bit value to write.
 *
 * \throw vix::exception::SerialWrite if the serial write fails.
 */
void
vix::serialWrite(std::ostream& out, std::int16_t value)
{
    uint8_t buffer[sizeof(value)];

    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;

    serialWriteFixedBuffer(out, buffer, sizeof(buffer));
}

/**
 * serialRead(int16_t) is an overloaded function that reads an unsigned
 * 16-bit value from the input stream.  This value is read in Big Endian
 * format for portability purposes.
 *
 * \param in            The input stream from which this value is read.
 * \param value         The unsigned 16-bit value to be read.
 *
 * \throw vix::exception::SerialRead if the serial read fails.
 */
void
vix::serialRead(std::istream& in, std::int16_t& value)
{
    uint8_t buffer[sizeof(value)];

    serialReadFixedBuffer(in, buffer, sizeof(buffer));

    value  = ((int16_t)buffer[0]) << 8;
    value |= ((int16_t)buffer[1]);
}

/**
 * serialWrite(int32_t) is an overloaded function that writes an unsigned
 * 32-bit value to the output stream.  This value is written in Big Endian
 * format for portability purposes.
 *
 * \param out           The output stream to which this value is written.
 * \param value         The unsigned 32-bit value to write.
 *
 * \throw vix::exception::SerialWrite if the serial write fails.
 */
void
vix::serialWrite(std::ostream& out, std::int32_t value)
{
    uint8_t buffer[sizeof(value)];

    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >>  8) & 0xFF;
    buffer[3] = (value      ) & 0xFF;

    serialWriteFixedBuffer(out, buffer, sizeof(buffer));
}

/**
 * serialRead(int32_t) is an overloaded function that reads an unsigned
 * 32-bit value from the input stream.  This value is read in Big Endian
 * format for portability purposes.
 *
 * \param in            The input stream from which this value is read.
 * \param value         The unsigned 32-bit value to be read.
 *
 * \throw vix::exception::SerialRead if the serial read fails.
 */
void
vix::serialRead(std::istream& in, std::int32_t& value)
{
    uint8_t buffer[sizeof(value)];

    serialReadFixedBuffer(in, buffer, sizeof(buffer));

    value  = ((int32_t)buffer[0]) << 24;
    value |= ((int32_t)buffer[1]) << 16;
    value |= ((int32_t)buffer[2]) <<  8;
    value |= ((int32_t)buffer[3]);
}

/**
 * serialWrite(int64_t) is an overloaded function that writes an unsigned
 * 64-bit value to the output stream.  This value is written in Big Endian
 * format for portability purposes.
 *
 * \param out           The output stream to which this value is written.
 * \param value         The unsigned 64-bit value to write.
 *
 * \throw vix::exception::SerialWrite if the serial write fails.
 */
void
vix::serialWrite(std::ostream& out, std::int64_t value)
{
    uint8_t buffer[sizeof(value)];

    buffer[0] = (value >> 56) & 0xFF;
    buffer[1] = (value >> 48) & 0xFF;
    buffer[2] = (value >> 40) & 0xFF;
    buffer[3] = (value >> 32) & 0xFF;
    buffer[4] = (value >> 24) & 0xFF;
    buffer[5] = (value >> 16) & 0xFF;
    buffer[6] = (value >>  8) & 0xFF;
    buffer[7] = (value      ) & 0xFF;

    serialWriteFixedBuffer(out, buffer, sizeof(buffer));
}

/**
 * serialRead(int64_t) is an overloaded function that reads an unsigned
 * 64-bit value from the input stream.  This value is read in Big Endian
 * format for portability purposes.
 *
 * \param in            The input stream from which this value is read.
 * \param value         The unsigned 64-bit value to be read.
 *
 * \throw vix::exception::SerialRead if the serial read fails.
 */
void
vix::serialRead(std::istream& in, std::int64_t& value)
{
    uint8_t buffer[sizeof(value)];

    serialReadFixedBuffer(in, buffer, sizeof(buffer));

    value  = ((int64_t)buffer[0]) << 56;
    value |= ((int64_t)buffer[1]) << 48;
    value |= ((int64_t)buffer[2]) << 40;
    value |= ((int64_t)buffer[3]) << 32;
    value |= ((int64_t)buffer[4]) << 24;
    value |= ((int64_t)buffer[5]) << 16;
    value |= ((int64_t)buffer[6]) <<  8;
    value |= ((int64_t)buffer[7]);
}

/**
 * serialWrite(const std::string&) is an overloaded function that writes a
 * string to the output stream as a variable buffer.
 *
 * \param out           The output stream to which this value is written.
 * \param value         The string value to write.
 *
 * \throw vix::exception::SerialWrite if the serial write fails.
 */
void
vix::serialWrite(std::ostream& out, const std::string& value)
{
    //use a full 32-bit size field to support lines up to 4GB in size.
    serialWriteBuffer(out, value.data(), value.size(), 4);
}

/**
 * serialRead(std::string&) is an overloaded function that reads a
 * string from the input stream as a variable buffer.
 *
 * \param in            The input stream from which this value is read.
 * \param value         The string value to read.
 *
 * \throw vix::exception::SerialRead if the serial read fails.
 */
void
vix::serialRead(std::istream& in, std::string& value)
{
    uint32_t size = 0;

    //use a full 32-bit size field to support lines up to 4GB in size.
    serialRead(in, size);

    //resize the string
    value.resize(size);

    //read the complete string
    //TODO - this may not be platform-independent.
    serialReadFixedBuffer(in, &value[0], size);
}
