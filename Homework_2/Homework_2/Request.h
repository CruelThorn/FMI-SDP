/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task 2
 * @compiler VC
 *
 */
#ifndef REQUEST_H
#define REQUEST_H
#include <iostream>

class Request
{
public:
	Request();
	~Request();
	Request(const Request& other);
	Request& operator=(const Request& other);
	Request(int, int);

	int getFloor() const;
	int getTime() const;
	bool isTakenCareOf() const;
	void takeCareOf();
protected:
private:
	int floor;
	int time;
	bool takenCareOf;
};



#endif // REQUEST_H
