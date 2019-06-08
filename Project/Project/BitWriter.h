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
#ifndef BITWRITER_H
#define BITWRITER_H
#include <iostream>
#include <fstream>
#include <cstring>

class BitWriter
{
    public:
        BitWriter(std::ofstream&);
        ~BitWriter();
        BitWriter(const BitWriter& other);
        BitWriter& operator=(const BitWriter& other);
        void write(char*);
        void endFlush();
		bool isFull() const { return numOfBits == 8 ? 1 : 0; }
		int getFileSizeInBytes() const { return fileSizeInBytes; }
    protected:
    private:
        char buffer;
        int numOfBits;
        int fileSizeInBytes;
        void flush();
        std::ofstream& os;
};

#endif // BITWRITER_H
