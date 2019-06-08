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
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <cmath>

enum Direction
{
    UP,
    DOWN
};

class Elevator
{
public:
	Elevator();
	~Elevator();
	Elevator(const Elevator& other);
	Elevator& operator=(const Elevator& other);
	Elevator(int);

	void stopOnFloor();
	void goToFloor(int);
	void setDirection(int);
	void stopOnFloorMidway(int);

	Direction getDirection() const;
	int getCurrentFloor() const;
	const int getSpeed() const;
	int getArrivalTime(int);
protected:
private:
	const int speed = 5;
	int floors;
	int currentFloor;
	Direction dir;
	bool* hasToStop;
};
#endif // ELEVATOR_H
