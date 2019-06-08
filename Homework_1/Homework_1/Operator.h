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
#ifndef OPERATOR_H
#define OPERATOR_H


class Operator
{
public:
	friend class ListOfOperators;
	Operator();
	~Operator();
	Operator(const Operator& other);
	Operator& operator=(const Operator& other);

	Operator(char, char, int);
	char getSymbol() { return symbol; }
	char getOperat() { return operat; }
	int getAssociation() { return association; }
protected:
private:
	char symbol;
	char operat;
	int association;
	Operator* pNext;
};

#endif // OPERATOR_H
