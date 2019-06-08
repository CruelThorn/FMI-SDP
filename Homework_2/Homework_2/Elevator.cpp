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
#include "Elevator.h"

extern int time;

Elevator::Elevator()
{}

Elevator::~Elevator()
{
	delete[] hasToStop;
}

Elevator::Elevator(const Elevator& other)
{
	floors = other.floors;
	currentFloor = other.currentFloor;
	dir = other.dir;
	hasToStop = other.hasToStop;
}

Elevator& Elevator::operator=(const Elevator& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	floors = rhs.floors;
	currentFloor = rhs.currentFloor;
	dir = rhs.dir;
	hasToStop = rhs.hasToStop;
	return *this;
}

Elevator::Elevator(int _floors) :
	floors(_floors),
	currentFloor(1),
	dir(DOWN)
{
	hasToStop = new bool[_floors];
	for (int i = 0; i < _floors; i++) {
		hasToStop[i] = false;
	}
}

void Elevator::setDirection(int destionationFloor)
{
	if (currentFloor < destionationFloor) {
		dir = UP;
	}else {
		dir = DOWN;
	}
}

void Elevator::stopOnFloor()
{
	std::cout << time << " " << currentFloor << " ";
	if (dir == UP) {
		std::cout << "up\n";
	}else {
		std::cout << "down\n";
	}
}

void Elevator::goToFloor(int _floor)
{
	setDirection(_floor);
	while (currentFloor != _floor) {
		if (hasToStop[currentFloor - 1] == true) {
			hasToStop[currentFloor - 1] = false;
			stopOnFloor();
		}
		if (dir == UP) {
			currentFloor++;
		}else {
			currentFloor--;
		}
		time += speed;
	}
	hasToStop[_floor - 1] = false;
	stopOnFloor();
}

void Elevator::stopOnFloorMidway(int midFloor)
{
	hasToStop[midFloor - 1] = true;
}

Direction Elevator::getDirection()const
{
	return dir;
}

int Elevator::getCurrentFloor()const
{
	return currentFloor;
}

const int Elevator::getSpeed()const
{
	return speed;
}

int Elevator::getArrivalTime(int destinationFloor)
{
	return time + abs(destinationFloor - currentFloor)*speed;
}

