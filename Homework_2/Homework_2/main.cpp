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
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Elevator.h"
#include "Request.h"
#include "Queue.h"
using namespace std;

int time = 0;

int main(int argc, char * argv[])
{
	//N - number of floors
	//K - number of requests
    int n, k;
    ifstream file;
    file.open(argv[1]);
	//Get floors number from file
    file >> n;
	//Get requests number from file
    file >> k;
    Queue<Request> requestQueue;
    Elevator elevator(n);
	//Extract requests from file
	for (int i = 0; i < k; i++) {
		string requestType;
		file >> requestType;
		if (requestType == "call") {
			string direction;
			int fromFloor;
			int fromTime;
			file >> direction >> fromFloor >> fromTime;
			Request newRequest(fromFloor, fromTime);
			requestQueue.enqueue(newRequest);
		}else if (requestType == "go") {
			int fromFloor;
			int fromTime;
			file >> fromFloor >> fromTime;
			Request newRequest(fromFloor, fromTime);
			requestQueue.enqueue(newRequest);
		}else {
			cout << "Incorrect request\n";
		}
	}
    file.close();

	//Set the time to the beginning of the first call
    time = requestQueue.top().getTime();
	//Start the simulation
	while (!requestQueue.isEmpty()) {
		if (requestQueue.top().isTakenCareOf()) {
			requestQueue.dequeue();
		}else {
			if (time < requestQueue.top().getTime()) {
				time = requestQueue.top().getTime();
			}
			int expectedArrivalTime = time + abs(requestQueue.top().getFloor() - elevator.getCurrentFloor()) * elevator.getSpeed();
			node<Request>* tmp;
			tmp = requestQueue.getFront();

			while ((tmp != 0) && (tmp->data.getTime() <= expectedArrivalTime)) {
				if (!tmp->data.isTakenCareOf()) {
					if ((tmp->data.getFloor() <= max(elevator.getCurrentFloor(), requestQueue.top().getFloor())) &&
						(tmp->data.getFloor() >= min(elevator.getCurrentFloor(), requestQueue.top().getFloor()))) {
						if (tmp->data.getTime() <= elevator.getArrivalTime(tmp->data.getFloor())) {
							elevator.stopOnFloorMidway(tmp->data.getFloor());
							tmp->data.takeCareOf();
						}
					}
				}
				tmp = tmp->next;
			}
			elevator.goToFloor(requestQueue.top().getFloor());
			requestQueue.dequeue();
		}
	}

    return 0;
}





