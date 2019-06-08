/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task Project
 * @compiler VC
 *
 */
#include "BitWriter.h"

BitWriter::BitWriter(std::ofstream& _os):
    os(_os),
    buffer(0),
    numOfBits(0),
    fileSizeInBytes(0)
{}

BitWriter::~BitWriter()
{}

BitWriter::BitWriter(const BitWriter& other):
    os(other.os),
    buffer(other.buffer),
    numOfBits(other.numOfBits),
    fileSizeInBytes(other.fileSizeInBytes)
{}

BitWriter& BitWriter::operator=(const BitWriter& rhs)
{
	if (this == &rhs) {
		return *this;
	}
    this->buffer = rhs.buffer;
    this->numOfBits = rhs.numOfBits;
    fileSizeInBytes = rhs.fileSizeInBytes;
    return *this;
}

void BitWriter::flush()
{
	os.write((char*)&buffer, sizeof(buffer));
	buffer = numOfBits = 0;
}

void BitWriter::endFlush()
{
	buffer = buffer << (8 - numOfBits);
	flush();
}

void BitWriter::write(char* h_code)
{
	for (int i = 0; i < strlen(h_code); i++) {
		if (isFull()) {
			flush();
			fileSizeInBytes++;
		}
		buffer = buffer << 1;
		numOfBits++;
		if (h_code[i] == '1') {
			buffer |= 1;
		}
	}
}
