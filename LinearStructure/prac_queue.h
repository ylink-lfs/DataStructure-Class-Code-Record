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
	seq_queue() : front(0), rear(1) {}
	void clear() { queue_body.clear(); front = 0; rear = 1; }
	size_t size() const { return (rear - front < 0 ? (sqlist<T>::max_size() + rear - front) : rear - front) - 1; }
	bool empty() const { return rear - front == 1; }
	void push(const T& elem);
	void pop();
	T top() const { return queue_body[front]; }
};

template<typename T>
void seq_queue<T>::push(const T& elem)
{
	if (rear == front)
	{
		std::cerr << "queue is full" << '\n';
		return;
	}
	queue_body[rear - 1] = elem;
	rear++;
	if (rear >= sqlist<T>::max_size())
		rear = 0;
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
	if (front >= sqlist<T>::max_size())
		front = 0;
}

template<typename T>
class lk_queue
{
private:
	Forward_list<T> queue_body;
	Forward_list<T>::iterator rear;
	Forward_list<T>::iterator front;
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