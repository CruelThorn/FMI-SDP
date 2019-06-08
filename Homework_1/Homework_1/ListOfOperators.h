/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task 1
 * @compiler VC
 *
 */
#ifndef LISTOFOPERATORS_H
#define LISTOFOPERATORS_H

#include <iostream>
#include "Operator.h"

class ListOfOperators
{
public:
	ListOfOperators();
	~ListOfOperators();
	ListOfOperators(const ListOfOperators& other) = delete;
	ListOfOperators& operator=(const ListOfOperators& other) = delete;
	void Append(char, char, int);
	Operator* pHead;
	Operator* pTail;
	char getTrueOperator(char);
protected:
private:
	Operator* operators;
};

#endif // LISTOFOPERATORS_H
