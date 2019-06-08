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
#include "Operator.h"

Operator::Operator()
{}

Operator::~Operator()
{}

Operator::Operator(const Operator& other)
{
	symbol = other.symbol;
	operat = other.operat;
	association = other.association;
	pNext = other.pNext;
}

Operator& Operator::operator=(const Operator& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	symbol = rhs.symbol;
	operat = rhs.operat;
	association = rhs.association;
	pNext = rhs.pNext;
	return *this;
}

Operator::Operator(char s, char o, int a) :
	symbol(s),
	operat(o),
	association(a)
{}
