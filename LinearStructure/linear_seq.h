#pragma once
#include <stdexcept>
#include <memory>
#include <string>

template<typename T>
class sqlist
{
private:
	static const size_t MAXsize = 100;
	std::unique_ptr<T[]> elem;
	size_t length;
	
public:
	sqlist() : elem(new T[MAXsize]), length(0) {}

	T& operator[](const size_t i);
	const T& operator[](const size_t i) const;
	size_t size() const;
	static size_t max_size() { return sqlist::MAXsize; }
	size_t find(const T& target) const;
	void insert(const T& target, const size_t location);
	void erase(const size_t location);
	void push_back(const T& target);
	void clear();
	bool empty() const;
	static const size_t npos = 0xffffffffu;
};

template<typename T>
T& sqlist<T>::operator[](const size_t i)
{
	if (i >= length)
	{
		throw std::out_of_range(std::string("Index " + std::to_string(i) +
			" is out of range [0, " + std::to_string(length) + ").").c_str());
	}
	return elem[i];
}

template<typename T>
const T& sqlist<T>::operator[](const size_t i) const
{
	if (i >= length)
	{
		throw std::out_of_range(std::string("Index " + std::to_string(i) +
			" is out of range [0, " + std::to_string(length) + ").").c_str());
	}
	return elem[i];
}

template<typename T>
size_t sqlist<T>::size() const
{
	return length;
}

template<typename T>
size_t sqlist<T>::find(const T& target) const
{
	for (size_t i = 0; i < length; i++)
	{
		if (elem[i] == target)
		{
			return i;
		}
	}
	return npos;
}

template<typename T>
void sqlist<T>::push_back(const T& target)
{
	if (length == MAXsize)
	{
		throw std::overflow_error("Sequential list is full.");
	}
	else
	{
		elem[length++] = target;
	}
}

template<typename T>
void sqlist<T>::insert(const T& target, const size_t location)
{
	if (location > length)
	{
		throw std::out_of_range(std::string("Index " + std::to_string(location) +
			" is out of range [0, " + std::to_string(length - 1) + ").").c_str());
	}
	else if (length == MAXsize)
	{
		throw std::overflow_error("Sequential list is full.");
	}
	else
	{
		for (size_t i = length - 1; i >= location && i != npos; i--)
		{
			elem[i + 1] = elem[i];
		}
		elem[location] = target;
		length++;
	}
}

template<typename T>
void sqlist<T>::erase(const size_t location)
{
	if (location >= length)
	{
		throw std::out_of_range(std::string("Index " + std::to_string(location) +
			" is out of range [0, " + std::to_string(length - 1) + ").").c_str());
	}
	else
	{
		for (size_t i = location; i < length; i++)
		{
			elem[i] = elem[i + 1];
		}
		length--;
	}
}

template<typename T>
void sqlist<T>::clear()
{
	length = 0;
}

template<typename T>
bool sqlist<T>::empty() const
{
	return length == 0 ? true : false;
}