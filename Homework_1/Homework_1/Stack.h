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
#pragma once

#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;

template <class Type>
class Stack
{
public:
	Stack();
	~Stack();
	void push(const Type&);
	void pop();
	Type top();
	bool isEmpty()const;
	size_t getSize();
protected:
private:
	Type* elements;
	size_t size;
	size_t capacity;
	void setSize(size_t);
};

template<class Type>
Stack<Type>::Stack()
{
	elements = NULL;
	size = 0;
	capacity = 0;
}

template<class Type>
Stack<Type>::~Stack()
{
	delete[] elements;
}

template<class Type>
void Stack<Type>::push(const Type& data)
{
	if (capacity == 0) {
		setSize(2);
	}
	else if (size == capacity) {
		setSize(2 * capacity);
	}
	elements[size] = data;
	size++;
}

template<class Type>
void Stack<Type>::pop()
{
	if (size > 0) {
		size--;
	}
	else {
		cerr << "Error!\n";
	}
	if (size == 0) {
		delete[] elements;
		elements = NULL;
		capacity = 0;
	}
	else if (size <= capacity / 4) {
		setSize(capacity / 2);
	}
}

template <class Type>
Type Stack<Type>::top()
{
	if (!isEmpty()) {
		return elements[size - 1];
	}
	else {
		return Type();
	}
}

template<class Type>
bool Stack<Type>::isEmpty() const
{
	return (size == 0);
}

template<class Type>
void Stack<Type>::setSize(size_t newSize)
{
	Type* newElements = new Type[newSize];
	for (unsigned int i = 0; i < size; i++) {
		newElements[i] = elements[i];
	}
	delete[] elements;
	elements = NULL;
	elements = newElements;
	capacity = newSize;
}

template<class Type>
size_t Stack<Type>::getSize()
{
	return size;
}

#endif // STACK_H
