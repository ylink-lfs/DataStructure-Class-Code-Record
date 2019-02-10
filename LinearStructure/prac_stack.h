#pragma once
#include <iostream>
#include "linear_linked.h"
#include "linear_seq.h"

template<typename T>
class seq_stack
{
private:
	sqlist<T> stack_body;
public:
	void clear() { stack_body.clear(); }
	size_t size() const { return stack_body.size(); }
	bool empty() const { return stack_body.empty(); }
	void push(const T& elem);
	void pop();
	T top() const { return stack_body[stack_body.size() - 1]; }
};

template<typename T>
void seq_stack<T>::push(const T& elem)
{
	if (stack_body.size() == stack_body.max_size())
	{
		std::cerr << "Stack is full" << '\n';
		return;
	}
	stack_body.push_back(elem);
}
template<typename T>
void seq_stack<T>::pop()
{
	if (stack_body.empty())
	{
		std::cerr << "Stack is empty" << '\n';
		return;
	}
	stack_body.erase(stack_body.size() - 1);
}

template<typename T>
class lk_stack
{
private:
	Forward_list<T> stack_body;
public:
	void clear() { stack_body.clear(); }
	size_t size() const { return stack_body.size(); }
	bool empty() const { return stack_body.empty(); }
	void push(const T& elem);
	void pop();
	T top() const { return stack_body.begin()->elem; }
};

template<typename T>
void lk_stack<T>::push(const T& elem)
{
	stack_body.push_front(elem);
}

template<typename T>
void lk_stack<T>::pop()
{
	if (stack_body.empty())
	{
		std::cerr << "Stack is empty" << '\n';
		return;
	}
	stack_body.pop_front();
}