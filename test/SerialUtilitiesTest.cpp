#include <gtest/gtest.h>
#include <vix/SerialUtilities.h>

#include <sstream>
#include <vector>

using namespace std;
using namespace vix;

/**
 * serialWriteFixed should write a fixed buffer of the given size to the given
 * stream.
 */
TEST(SerialUtilitiesTest, serialWriteFixedBufferBase)
{
    const string TEST_BUFFER = "Test 1234";

    stringstream ss;

    serialWriteFixedBuffer(ss, TEST_BUFFER.data(), TEST_BUFFER.size());

    //the write should write exactly the right number of bytes.
    EXPECT_EQ(TEST_BUFFER.size(), ss.str().size());
    //the write should be just the string data.
    EXPECT_EQ(TEST_BUFFER, ss.str());
}

/**
 * serialWriteFixedBuffer should throw a serial write exception if the stream is
 * bad after writing.
 */
TEST(SerialUtilitiesTest, serialWriteFixedBufferBad)
{
    const string TEST_BUFFER = "Test 1234";

    //make a bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //this should cause an exception to be thrown.
    EXPECT_THROW(
        serialWriteFixedBuffer(ss, TEST_BUFFER.data(), TEST_BUFFER.size()), 
        vix::exception::SerialWrite);
}

/**
 * serialReadFixed should read a fixed buffer of the given size from the given
 * stream.
 */
TEST(SerialUtilitiesTest, serialReadFixedBufferBase)
{
    const string EXPECTED_RESULT = "Test 1234";

    vector<uint8_t> readBuffer(EXPECTED_RESULT.size(), 0);

    stringstream ss(EXPECTED_RESULT);

    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //The read should have read the correct number of bytes.
    EXPECT_EQ(EXPECTED_RESULT.size(), readBuffer.size());
    //the buffers should match
    EXPECT_EQ(0, memcmp(EXPECTED_RESULT.data(), &readBuffer[0], readBuffer.size()));
}

/**
 * serialReadFixedBuffer should throw a serial read exception if the stream read
 * fails.
 */
TEST(SerialUtilitiesTest, serialReadFixedBufferException)
{
    const string EXPECTED_RESULT = "Test 1234";

    vector<uint8_t> readBuffer(EXPECTED_RESULT.size(), 0);

    stringstream ss;

    //this should cause an exception to be thrown.
    EXPECT_THROW(
        serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size()),
        vix::exception::SerialRead);
}

/**
 * calling serialWriteFixedBuffer and serialReadFixedBuffer should result in the
 * same buffer being read / written.
 */
TEST(SerialUtilitiesTest, serialReadWriteFixedBuffer)
{
    const vector<uint8_t> EXPECTED_BUFFER{0x40,0x09,0x19,0xab,0x23};
    vector<uint8_t> readBuffer(EXPECTED_BUFFER.size(), 0);

    //the test stream
    stringstream ss;

    //write the buffer to the stream
    serialWriteFixedBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size());

    //read the buffer from the stream
    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //the two buffers should match
    EXPECT_EQ(0, memcmp(&EXPECTED_BUFFER[0], &readBuffer[0], readBuffer.size()));
}

/**
 * serialWriteBuffer writes a variable length buffer to the stream, first
 * writing the size of the buffer in Big Endian format.
 */
TEST(SerialUtilitiesTest, serialWriteBuffer)
{
    const vector<uint8_t> EXPECTED_BUFFER{0x40,0x09,0x19,0xab,0x23};
    vector<uint8_t> readBuffer(EXPECTED_BUFFER.size()+2, 0);

    //create the stream
    stringstream ss;

    //write the variable buffer
    serialWriteBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size());

    //read the buffer
    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //the size should be 2 bytes Big Endian
    EXPECT_EQ(0, readBuffer[0]);
    EXPECT_EQ(EXPECTED_BUFFER.size(), (size_t)readBuffer[1]);

    //the expected buffer should have been written after these bytes
    EXPECT_EQ(0, memcmp(&EXPECTED_BUFFER[0], &readBuffer[2], EXPECTED_BUFFER.size()));
}

/**
 * serialWriteBuffer writes a variable length buffer to the stream, first
 * writing the size of the buffer in Big Endian format.  Three byte version.
 */
TEST(SerialUtilitiesTest, serialWriteBuffer3)
{
    const vector<uint8_t> EXPECTED_BUFFER{0x40,0x09,0x19,0xab,0x23};
    vector<uint8_t> readBuffer(EXPECTED_BUFFER.size()+3, 0);

    //create the stream
    stringstream ss;

    //write the variable buffer
    serialWriteBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size(), 3);

    //read the buffer
    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //the size should be 3 bytes Big Endian
    EXPECT_EQ(0, readBuffer[0]);
    EXPECT_EQ(0, readBuffer[1]);
    EXPECT_EQ(EXPECTED_BUFFER.size(), (size_t)readBuffer[2]);

    //the expected buffer should have been written after these bytes
    EXPECT_EQ(0, memcmp(&EXPECTED_BUFFER[0], &readBuffer[3], EXPECTED_BUFFER.size()));
}

/**
 * serialWriteBuffer writes a variable length buffer to the stream, first
 * writing the size of the buffer in Big Endian format.  Four byte version.
 */
TEST(SerialUtilitiesTest, serialWriteBuffer4)
{
    const vector<uint8_t> EXPECTED_BUFFER{0x40,0x09,0x19,0xab,0x23};
    vector<uint8_t> readBuffer(EXPECTED_BUFFER.size()+4, 0);

    //create the stream
    stringstream ss;

    //write the variable buffer
    serialWriteBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size(), 4);

    //read the buffer
    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //the size should be 4 bytes Big Endian
    EXPECT_EQ(0, readBuffer[0]);
    EXPECT_EQ(0, readBuffer[1]);
    EXPECT_EQ(0, readBuffer[2]);
    EXPECT_EQ(EXPECTED_BUFFER.size(), (size_t)readBuffer[3]);

    //the expected buffer should have been written after these bytes
    EXPECT_EQ(0, memcmp(&EXPECTED_BUFFER[0], &readBuffer[4], EXPECTED_BUFFER.size()));
}

/**
 * serialWriteBuffer writes a variable length buffer to the stream, first
 * writing the size of the buffer in Big Endian format.  One byte version.
 */
TEST(SerialUtilitiesTest, serialWriteBuffer1)
{
    const vector<uint8_t> EXPECTED_BUFFER{0x40,0x09,0x19,0xab,0x23};
    vector<uint8_t> readBuffer(EXPECTED_BUFFER.size()+1, 0);

    //create the stream
    stringstream ss;

    //write the variable buffer
    serialWriteBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size(), 1);

    //read the buffer
    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //the size should be 1 byte Big Endian
    EXPECT_EQ(EXPECTED_BUFFER.size(), (size_t)readBuffer[0]);

    //the expected buffer should have been written after these bytes
    EXPECT_EQ(0, memcmp(&EXPECTED_BUFFER[0], &readBuffer[1], EXPECTED_BUFFER.size()));
}

/**
 * serialWriteBuffer fails with an assertion if an unsupported size byte size is
 * used.
 */
TEST(SerialUtilitiesTest, serialWriteBufferAssert)
{
    const vector<uint8_t> EXPECTED_BUFFER{0x40,0x09,0x19,0xab,0x23};
    vector<uint8_t> readBuffer(EXPECTED_BUFFER.size()+1, 0);

    //create the stream
    stringstream ss;

    //Will cause an out-of-bounds assertion error.
    EXPECT_DEATH(
        serialWriteBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size(), 0),
        "sizeBytes >= 1 && sizeBytes <= 4");

    //Will cause an out-of-bounds assertion error.
    EXPECT_DEATH(
        serialWriteBuffer(ss, &EXPECTED_BUFFER[0], EXPECTED_BUFFER.size(), 5),
        "sizeBytes >= 1 && sizeBytes <= 4");
}

/**
 * serialWrite(uint8_t) writes an unsigned 8-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_uint8_t)
{
    const uint8_t EXPECTED_VALUE = 21;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, buffer[0]);
}

/**
 * serialWrite(uint8_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_uint8_t_exception)
{
    const uint8_t EXPECTED_VALUE = 21;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a uint8_t value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(uint8_t) reads an unsigned 8-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_uint8_t)
{
    const uint8_t EXPECTED_VALUE = 21;
    uint8_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(uint8_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_uint8_t_exception)
{
    const uint8_t EXPECTED_VALUE = 21;
    uint8_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(uint16_t) writes an unsigned 16-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_uint16_t)
{
    const uint16_t EXPECTED_VALUE = 0x2d19;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the big-endian representation
    //of the expected_value
    EXPECT_EQ(EXPECTED_VALUE >> 8, buffer[0]);
    EXPECT_EQ(EXPECTED_VALUE & 0xFF, buffer[1]);
}

/**
 * serialWrite(uint16_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_uint16_t_exception)
{
    const uint16_t EXPECTED_VALUE = 0x2d19;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(uint16_t) reads an unsigned 16-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_uint16_t)
{
    const uint16_t EXPECTED_VALUE = 0x2d19;
    uint16_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(uint16_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_uint16_t_exception)
{
    const uint16_t EXPECTED_VALUE = 0x2d19;
    uint16_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(uint32_t) writes an unsigned 32-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_uint32_t)
{
    const uint32_t EXPECTED_VALUE = 0x2d198a03;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the big-endian representation
    //of the expected_value
    EXPECT_EQ((EXPECTED_VALUE >> 24) & 0xFF, buffer[0]);
    EXPECT_EQ((EXPECTED_VALUE >> 16) & 0xFF, buffer[1]);
    EXPECT_EQ((EXPECTED_VALUE >>  8) & 0xFF, buffer[2]);
    EXPECT_EQ( EXPECTED_VALUE        & 0xFF, buffer[3]);
}

/**
 * serialWrite(uint32_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_uint32_t_exception)
{
    const uint32_t EXPECTED_VALUE = 0x2d198a03;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(uint32_t) reads an unsigned 32-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_uint32_t)
{
    const uint32_t EXPECTED_VALUE = 0x2d198a03;
    uint32_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(uint32_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_uint32_t_exception)
{
    const uint32_t EXPECTED_VALUE = 0x2d198a03;
    uint32_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(uint64_t) writes an unsigned 64-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_uint64_t)
{
    const uint64_t EXPECTED_VALUE = 0x2d198a0304050607;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the big-endian representation
    //of the expected_value
    EXPECT_EQ((EXPECTED_VALUE >> 56) & 0xFF, buffer[0]);
    EXPECT_EQ((EXPECTED_VALUE >> 48) & 0xFF, buffer[1]);
    EXPECT_EQ((EXPECTED_VALUE >> 40) & 0xFF, buffer[2]);
    EXPECT_EQ((EXPECTED_VALUE >> 32) & 0xFF, buffer[3]);
    EXPECT_EQ((EXPECTED_VALUE >> 24) & 0xFF, buffer[4]);
    EXPECT_EQ((EXPECTED_VALUE >> 16) & 0xFF, buffer[5]);
    EXPECT_EQ((EXPECTED_VALUE >>  8) & 0xFF, buffer[6]);
    EXPECT_EQ( EXPECTED_VALUE        & 0xFF, buffer[7]);
}

/**
 * serialWrite(uint64_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_uint64_t_exception)
{
    const uint64_t EXPECTED_VALUE = 0x2d198a0304050607;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(uint64_t) reads an unsigned 64-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_uint64_t)
{
    const uint64_t EXPECTED_VALUE = 0x2d198a0304050607;
    uint64_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(uint64_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_uint64_t_exception)
{
    const uint64_t EXPECTED_VALUE = 0x2d198a0304050607;
    uint64_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(int8_t) writes an unsigned 8-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_int8_t)
{
    const int8_t EXPECTED_VALUE = 21;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, buffer[0]);
}

/**
 * serialWrite(int8_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_int8_t_exception)
{
    const int8_t EXPECTED_VALUE = 21;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a int8_t value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(int8_t) reads an unsigned 8-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_int8_t)
{
    const int8_t EXPECTED_VALUE = 21;
    int8_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(int8_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_int8_t_exception)
{
    const int8_t EXPECTED_VALUE = 21;
    int8_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(int16_t) writes an unsigned 16-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_int16_t)
{
    const int16_t EXPECTED_VALUE = 0x2d19;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the big-endian representation
    //of the expected_value
    EXPECT_EQ(EXPECTED_VALUE >> 8, buffer[0]);
    EXPECT_EQ(EXPECTED_VALUE & 0xFF, buffer[1]);
}

/**
 * serialWrite(int16_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_int16_t_exception)
{
    const int16_t EXPECTED_VALUE = 0x2d19;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(int16_t) reads an unsigned 16-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_int16_t)
{
    const int16_t EXPECTED_VALUE = 0x2d19;
    int16_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(int16_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_int16_t_exception)
{
    const int16_t EXPECTED_VALUE = 0x2d19;
    int16_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(int32_t) writes an unsigned 32-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_int32_t)
{
    const int32_t EXPECTED_VALUE = 0x2d198a03;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the big-endian representation
    //of the expected_value
    EXPECT_EQ((EXPECTED_VALUE >> 24) & 0xFF, buffer[0]);
    EXPECT_EQ((EXPECTED_VALUE >> 16) & 0xFF, buffer[1]);
    EXPECT_EQ((EXPECTED_VALUE >>  8) & 0xFF, buffer[2]);
    EXPECT_EQ( EXPECTED_VALUE        & 0xFF, buffer[3]);
}

/**
 * serialWrite(int32_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_int32_t_exception)
{
    const int32_t EXPECTED_VALUE = 0x2d198a03;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(int32_t) reads an unsigned 32-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_int32_t)
{
    const int32_t EXPECTED_VALUE = 0x2d198a03;
    int32_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(int32_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_int32_t_exception)
{
    const int32_t EXPECTED_VALUE = 0x2d198a03;
    int32_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(int64_t) writes an unsigned 64-bit value.
 */
TEST(SerialUtilitiesTest, serialWrite_int64_t)
{
    const int64_t EXPECTED_VALUE = 0x2d198a0304050607;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialReadFixedBuffer(ss, buffer, sizeof(EXPECTED_VALUE));

    //the value read into the buffer should match the big-endian representation
    //of the expected_value
    EXPECT_EQ((EXPECTED_VALUE >> 56) & 0xFF, buffer[0]);
    EXPECT_EQ((EXPECTED_VALUE >> 48) & 0xFF, buffer[1]);
    EXPECT_EQ((EXPECTED_VALUE >> 40) & 0xFF, buffer[2]);
    EXPECT_EQ((EXPECTED_VALUE >> 32) & 0xFF, buffer[3]);
    EXPECT_EQ((EXPECTED_VALUE >> 24) & 0xFF, buffer[4]);
    EXPECT_EQ((EXPECTED_VALUE >> 16) & 0xFF, buffer[5]);
    EXPECT_EQ((EXPECTED_VALUE >>  8) & 0xFF, buffer[6]);
    EXPECT_EQ( EXPECTED_VALUE        & 0xFF, buffer[7]);
}

/**
 * serialWrite(int64_t) should throw a serial write exception when writing to a
 * bad stream.
 */
TEST(SerialUtilitiesTest, serialWrite_int64_t_exception)
{
    const int64_t EXPECTED_VALUE = 0x2d198a0304050607;
    uint8_t buffer[sizeof(EXPECTED_VALUE)] = {0};

    //bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //writing a value to a bad stream should result in an exception
    //being thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_VALUE),
        vix::exception::SerialWrite);
}

/**
 * serialRead(int64_t) reads an unsigned 64-bit value.
 */
TEST(SerialUtilitiesTest, serialRead_int64_t)
{
    const int64_t EXPECTED_VALUE = 0x2d198a0304050607;
    int64_t readValue;

    //stream
    stringstream ss;

    //write the value to the stream.
    serialWrite(ss, EXPECTED_VALUE);

    //read the value from the stream
    serialRead(ss, readValue);

    //the value read into the buffer should match the expected value.
    EXPECT_EQ(EXPECTED_VALUE, readValue);
}

/**
 * serialRead(int64_t) should throw an exception when reading would truncate.
 */
TEST(SerialUtilitiesTest, serialRead_int64_t_exception)
{
    const int64_t EXPECTED_VALUE = 0x2d198a0304050607;
    int64_t readValue;

    //stream
    stringstream ss;

    //reading from an empty stream causes an exception to be thrown
    EXPECT_THROW(
        serialRead(ss, readValue),
        vix::exception::SerialRead);
}

/**
 * serialWrite(std::string) should write a variable length buffer with the
 * string value.
 */
TEST(SerialUtilitiesTest, serialWrite_string)
{
    const string EXPECTED_STRING{"The string to be written."};
    vector<uint8_t> readBuffer(EXPECTED_STRING.size()+4, 0);

    //create the stream
    stringstream ss;

    //write the string
    serialWrite(ss, EXPECTED_STRING);

    //read the buffer
    serialReadFixedBuffer(ss, &readBuffer[0], readBuffer.size());

    //the size should be 4 bytes Big Endian
    EXPECT_EQ(0, readBuffer[0]);
    EXPECT_EQ(0, readBuffer[1]);
    EXPECT_EQ(0, readBuffer[2]);
    EXPECT_EQ(EXPECTED_STRING.size(), (size_t)readBuffer[3]);

    //the expected buffer should have been written after these bytes
    EXPECT_EQ(0, memcmp(EXPECTED_STRING.data(), &readBuffer[4], EXPECTED_STRING.size()));
}

/**
 * serialWrite(std::string) should throw an exception when the stream is bad.
 */
TEST(SerialUtilitiesTest, serialWrite_string_exception)
{
    const string EXPECTED_STRING{"The string to be written."};

    //create a bad stream
    stringstream ss;
    ss.setstate(ios::badbit);

    //Writing the string should cause an exception to be thrown.
    EXPECT_THROW(
        serialWrite(ss, EXPECTED_STRING),
        vix::exception::SerialWrite);
}

/**
 * serialRead(std::string) should read a string previously written to a stream
 * by serialWrite(std::string).
 */
TEST(SerialUtilitiesTest, serialRead_string)
{
    const string EXPECTED_STRING{"The string to be written."};
    string readString;

    //create the stream
    stringstream ss;

    //write the string
    serialWrite(ss, EXPECTED_STRING);

    //read the string
    serialRead(ss, readString);

    //the two strings should match
    EXPECT_EQ(EXPECTED_STRING, readString);
}

/**
 * serialRead(std::string) should throw an exception if the string cannot be
 * read.
 */
TEST(SerialUtilitiesTest, serialRead_string_exception)
{
    string readString;

    //create the stream
    stringstream ss;

    //read a string from an empty stream.  Should throw.
    EXPECT_THROW(
        serialRead(ss, readString),
        vix::exception::SerialRead);
}
