#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <cstring>
#include <initializer_list>
#include <exception>

using std::unique_ptr;
using std::string;
using std::initializer_list;
using std::strlen;
using std::copy;
using std::ostream;
using std::istream;
using std::out_of_range;

//No need to rewrite copy ctor, dtor, assignment operator
//Note that I use index 0 as the start, not 1 like textbook
//Valid index value is [0, len), use exception to warn access out of range
template<typename T>
class sstring
{
private:
	unique_ptr<T[]> str;
	int len;
	int capacity;
	const static int npos = 0x7fffffff;
	int compare(const sstring<T>& s) const;
public:
	sstring(const char* s);
	sstring(const string& s);
	sstring(initializer_list<T>& s);
	bool empty() const { return len == 0; }
	int size() const { return len; }
	void clear() { len = 0; }
	void shrink_to_fit();
	void reserve(const int val);
	bool operator==(const sstring<T>& s) const { return compare(s) == 0; }
	bool operator!=(const sstring<T>& s) const { return compare(s) != 0; }
	bool operator>(const sstring<T>& s) const { return compare(s) > 0; }
	bool operator<(const sstring<T>& s) const { return compare(s) < 0; }
	const T& operator[](const int i) const;
	T& operator[](const int i);
	void concat(const sstring<T>& s);
	sstring<T> substr(const int start_pos, const int len);
	int appear_pos(const sstring<T>& s, const int start_pos);
	void replace(const sstring<T>& s);
	void insert(const sstring<T>& s, const int insert_pos);
	void remove(const int start_pos, const int len);

	friend ostream& operator<<(ostream& os, const sstring<T>& s)
	{
		for (const auto& elem : s.str)
			os << elem;
		return os;
	}
	friend istream& operator>>(istream& ist, sstring<T>& s)
	{
		const int bufsize = 500;
		T buf[bufsize];
		ist >> buf;
		int len = strlen(buf);
		s.reserve(len * 2);
		copy(buf, buf + len, s);
		s[len] = '\0';
	}
};

template<typename T>
int sstring<T>::compare(const sstring<T>& s) const
{
	int i = 0;
	while (str[i] && s.str[i] && str[i] == s.str[i])
		i++;
	return str[i] - s.str[i];
}

template<typename T>
sstring<T>::sstring(const char* s) : str(new T[2 * strlen(s)])
{
	len = strlen(s);
	capacity = 2 * len;
	copy(s, s + len, str.get());
	str[len] = '\0';
}

template<typename T>
sstring<T>::sstring(const string& s) : str(new T[2 * s.size()]), len(s.size()), capacity(2 * s.size())
{
	copy(s.begin(), s.end(), str.get());
	str[len] = '\0';
}

template<typename T>
sstring<T>::sstring(initializer_list<T>& s) : str(new T[2 * s.size()]), len(s.size()), capacity(2 * s.size())
{
	int i = 0;
	for (const auto& character : s)
	{
		str[i++] = character;
	}
	str[i] = '\0';
}

template<typename T>
void sstring<T>::shrink_to_fit()
{
	unique_ptr<T[]> tmp_ptr(new T[len]);
	copy(str.get(), str.get() + len, tmp_ptr.get());
	str.swap(tmp_ptr);
	capacity = len;
}

template<typename T>
void sstring<T>::reserve(const int val)
{
	unique_ptr<T[]> tmp_ptr(new T[val]);
	copy(str.get(), str.get() + len, tmp_ptr.get());
	str.swap(tmp_ptr);
	capacity = val;
}