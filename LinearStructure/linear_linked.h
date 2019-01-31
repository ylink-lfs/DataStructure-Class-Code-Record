#pragma once
#include <algorithm>
#include <stdexcept>
#include <utility>

template<typename T>
class Forward_list
{
private:
	struct node
	{
	public:
		T elem;
		node* next;
		node(T ele = T(), node* nxt = nullptr) : elem(ele), next(nxt) {}
	};
	node* head;
	size_t count;
public:
	using iterator = node*;

	Forward_list() : head(new node), count(0) {}
	~Forward_list();
	Forward_list(const Forward_list<T>& fl);
	Forward_list<T>& operator=(Forward_list<T> rhs);
	Forward_list(Forward_list<T>&& rhs);
	Forward_list<T>& operator=(Forward_list<T>&& rhs);

	void clear();
	bool empty() const { return count == 0 ? true : false; }
	void swap(Forward_list<T>& rhs) { std::swap(count, rhs.count); std::swap(head, rhs.head); }
	size_t size() const { return count; }
	iterator begin() const { return head->next; }
	iterator end() const { return nullptr; }

	void insert_after(iterator it, const T& elem);
	void erase_after(iterator it);
	void push_front(const T& elem);
	void pop_front();
	iterator find(const T& elem) const;
};

template<typename T>
Forward_list<T>::~Forward_list()
{
	iterator tmp = nullptr;
	iterator it = head;
	while (it)
	{
		tmp = it;
		it = it->next;
		delete tmp;
	}
}

template<typename T>
Forward_list<T>::Forward_list(const Forward_list<T>& fl)
{
	head = new node;
	count = fl.count;
	iterator from_it = fl.head->next;
	iterator to_it = head;
	while (from_it)
	{
		node* tmp = new node(from_it->elem, nullptr);
		to_it->next = tmp;
		to_it = to_it->next;
		from_it = from_it->next;
	}
}

template<typename T>
Forward_list<T>& Forward_list<T>::operator=(Forward_list<T> rhs)
{
	swap(rhs);
	return *this;
}

template<typename T>
Forward_list<T>::Forward_list(Forward_list<T>&& rhs)
{
	head = rhs.head;
	count = rhs.count;
	rhs.count = 0;
	rhs.head = nullptr;
}

template<typename T>
Forward_list<T>& Forward_list<T>::operator=(Forward_list<T>&& rhs)
{
	if (this != &rhs)
	{
		std::swap(head, rhs.head);
		std::swap(count, rhs.count);
	}
	return *this;
}

template<typename T>
void Forward_list<T>::clear()
{
	iterator tmp = nullptr;
	iterator it = head->next;
	while (it)
	{
		tmp = it;
		it = it->next;
		delete tmp;
	}
	count = 0;
}

template<typename T>
void Forward_list<T>::insert_after(iterator it, const T& elem)
{
	if (!it || it == head)
		throw std::out_of_range("Invalid iterator");
	node* tmp = new node(elem, it->next);
	it->next = tmp;
	count++;
}

template<typename T>
void Forward_list<T>::erase_after(iterator it)
{
	if (!it || it == head)
		throw std::out_of_range("Invalid iterator");
	node* tmp = it->next;
	it->next = tmp->next;
	delete tmp;
	count--;
}

template<typename T>
void Forward_list<T>::push_front(const T& elem)
{
	node* tmp = new node(elem, head->next);
	head->next = tmp;
	count++;
}

template<typename T>
void Forward_list<T>::pop_front()
{
	node* tmp = head;
	head = head->next;
	delete tmp;
	count--;

}

template<typename T>
typename Forward_list<T>::iterator Forward_list<T>::find(const T& elem) const
{
	iterator it = head->next;
	while (it)
	{
		if (it->elem == elem)
			return it;
		it = it->next;
	}
	return it;
}