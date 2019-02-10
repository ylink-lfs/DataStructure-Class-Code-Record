#pragma once
#include <iostream>
#include "linear_linked.h"
#include "linear_seq.h"

template<typename T>
class seq_queue
{
private:
	sqlist<T> queue_body;
	int front, rear;
public:
	seq_queue() : front(0), rear(0) { 
		for (int i = 0; i < sqlist<T>::max_size(); i++) 
			queue_body.push_back(T()); 
	}
	void clear() { front = 0; rear = 0; }
	size_t size() const { return rear - front; }
	bool empty() const { return front == rear; }
	void push(const T& elem);
	void pop();
	T top() const { return queue_body[front % sqlist<T>::max_size()]; }
};

template<typename T>
void seq_queue<T>::push(const T& elem)
{
	if (rear - front == sqlist<T>::max_size())
	{
		std::cerr << "queue is full" << '\n';
		return;
	}
	queue_body[rear % sqlist<T>::max_size()] = elem;
	rear++;
}
template<typename T>
void seq_queue<T>::pop()
{
	if (this->empty())
	{
		std::cerr << "queue is empty" << '\n';
		return;
	}
	front++;
}

template<typename T>
class lk_queue
{
private:
	Forward_list<T> queue_body;
	typename Forward_list<T>::iterator rear;
	typename Forward_list<T>::iterator front;
public:
	lk_queue() { queue_body.push_front(T()); rear = front = queue_body.begin(); }
	void clear() { 
		queue_body.clear(); queue_body.push_front(T()); rear = front = queue_body.begin();
	}
	size_t size() const { return queue_body.size() - 1; }
	bool empty() const { return queue_body.size() <= 1 ? true : false; }
	void push(const T& elem);
	void pop();
	T top() const { return front->next->elem; }
};

template<typename T>
void lk_queue<T>::push(const T& elem)
{
	queue_body.insert_after(rear, elem);
	rear = rear->next;
}

template<typename T>
void lk_queue<T>::pop()
{
	if (this->empty())
	{
		std::cerr << "queue is empty" << '\n';
		return;
	}
	queue_body.erase_after(front);
}