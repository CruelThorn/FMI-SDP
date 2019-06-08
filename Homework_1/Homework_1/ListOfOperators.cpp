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
#include "ListOfOperators.h"

ListOfOperators::ListOfOperators()
{
	pHead = pTail = NULL;
}

ListOfOperators::~ListOfOperators()
{
	Operator* pDel = pHead;
	while (pDel != NULL) {
		pHead = pHead->pNext;
		delete pDel;
		pDel = pHead;
	}
	pHead = pTail = NULL;
}

void ListOfOperators::Append(char s, char o, int a)
{
	if (pHead == NULL) {
		pTail = pHead = new Operator(s, o, a);
	}
	else {
		pTail->pNext = new Operator(s, o, a);
		pTail = pTail->pNext;
	}
}

char ListOfOperators::getTrueOperator(char op)
{
	Operator* tmp;
	tmp = pHead;
	while (tmp) {
		if (tmp->getSymbol() == op) {
			return tmp->getOperat();
		}
		else {
			tmp = tmp->pNext;
		}
	}
	std::cerr << "Error";
	return 0;
}

