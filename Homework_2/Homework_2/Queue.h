#pragma once
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
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<iostream>
#include<cstdlib>

template <class Type>
struct node{
    Type data;
    struct node *next;
};

template <class Type>
class Queue
{
public:
	Queue();
	~Queue();
	Queue(const Queue<Type>&);

	void enqueue(const Type&);
	void dequeue();
	Type& top();
	bool isEmpty();

	node<Type>* getFront();
private:
	node<Type> *rear;
	node<Type> *front;
};


template <class Type>
Queue<Type>::Queue()
{
	front = rear = NULL;
}

template <class Type>
Queue<Type>::~Queue()
{
	node<Type> *tmp = front;
	while (tmp != NULL) {
		front = tmp->next;
		delete tmp;
		tmp = front;
	}
	front = rear = NULL;
}

template <class Type>
Queue<Type>::Queue(const Queue<Type>& cpy)
{
	front = rear = NULL;
	node<Type>* tmp = cpy.getFront();
	while (tmp != NULL) {
		enqueue(tmp.data);
		tmp = tmp.next;
	}
}

template <class Type>
void Queue<Type>::enqueue(const Type& T)
{
	node<Type> *tmp = new node<Type>;
	tmp->data = T;
	tmp->next = NULL;
	if (front == NULL) {
		front = tmp;
	}else {
		rear->next = tmp;
	}
	rear = tmp;
}

template <class Type>
void Queue<Type>::dequeue()
{
	node<Type> *tmp = new node<Type>;
	if (front == NULL) {
		cout << "Queue is Empty\n";
	}else {
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template <class Type>
Type& Queue<Type>::top()
{
	return front->data;
}

template <class Type>
bool Queue<Type>::isEmpty()
{
	if (front == NULL) {
		return true;
	}else {
		return false;
	}
}

template <class Type>
node<Type>* Queue<Type>::getFront()
{
	return front;
}

#endif // QUEUE_H_INCLUDED
