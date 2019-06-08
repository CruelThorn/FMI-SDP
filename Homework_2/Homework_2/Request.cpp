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
#include "Request.h"

Request::Request()
{}

Request::~Request()
{}

Request::Request(const Request& other)
{
	floor = other.floor;
	time = other.time;
	takenCareOf = other.takenCareOf;
}

Request& Request::operator=(const Request& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	floor = rhs.floor;
	time = rhs.time;
	takenCareOf = rhs.takenCareOf;
	return *this;
}

Request::Request(int f, int t):
        floor(f),
        time(t),
        takenCareOf(false)
{}

void Request::takeCareOf()
{
	takenCareOf = true;
}

int Request::getFloor() const
{
	return floor;
}

int Request::getTime() const
{
	return time;
}

bool Request::isTakenCareOf() const
{
	return takenCareOf;
}
