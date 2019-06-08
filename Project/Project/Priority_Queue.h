/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Stoicho Ganchev
 * @idnumber 45177
 * @task Project
 * @compiler VC
 *
 */
#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED
#include <iostream>

template <class T>
struct q_node
{
	q_node();
	~q_node();
	q_node(T*, int);

	T* data;
	int priority;
	q_node* next;
};

template <class T>
q_node<T>::q_node()
{
	data = NULL;
	priority = 0;
	next = NULL;
}

template <class T>
q_node<T>::~q_node()
{
	delete data;
}

template <class T>
q_node<T>::q_node(T* _data, int _priority)
{
	data = _data;
	priority = _priority;
	next = NULL;
}

//Priority Queue
template <class T>
class priorityQueue
{
public:
	priorityQueue();
	~priorityQueue();

	void push(T*, int);
	T* pop();
	bool hasNext() const;
	bool isEmpty() const;
private:
	q_node<T>* front;
};

template <class T>
priorityQueue<T>::priorityQueue()
{
	front = NULL;
}

template <class T>
priorityQueue<T>::~priorityQueue()
{
	while (front) {
		q_node<T>* tmp = front;
		front = front->next;
		delete tmp;
	}
}

template <class T>
void priorityQueue<T>::push(T* _node, int priority)
{
	q_node<T>* newNode = new q_node<T>(_node, priority);
	q_node<T>* pos;
	if (!front) {
		front = newNode;
	}else if (newNode->priority < front->priority) {
		newNode->next = front;
		front = newNode;
	}else {
		pos = front;
		while (pos->next != NULL && newNode->priority > pos->next->priority) {
			pos = pos->next;
		}
		newNode->next = pos->next;
		pos->next = newNode;
	}
}

template <class T>
T* priorityQueue<T>::pop()
{
	if (!front) {
		std::cerr << "Queue is empty!\n";
		return 0;
	}else {
		q_node<T>* tmp = front;
		front = front->next;
		return tmp->data;
	}
}

template <class T>
bool priorityQueue<T>::hasNext() const
{
	if (front->next) {
		return true;
	}else {
		return false;
	}
}

template <class T>
bool priorityQueue<T>::isEmpty() const
{
	if (!front) {
		return true;
	}
	return false;
}

#endif // PRIORITY_QUEUE_H_INCLUDED