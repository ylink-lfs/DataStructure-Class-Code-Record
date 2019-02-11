//Chap 2 Section 7
#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
using std::vector;

//2.7.1, general find-union
template<typename T>
vector<T> find_union(const vector<T>& v1, const vector<T>& v2)
{
	vector<T> res;
	auto insert_distinct = [&](const vector<T>& v) {
		for (auto elem : v)
		{
			typename vector<T>::iterator find_res;
			if (std::find(res.begin(), res.end(), elem) == res.end())
			{
				res.push_back(elem);
			}
		}
	};
	insert_distinct(v1);
	insert_distinct(v2);
	return res;
}

//2.7.2, find ordered_union
template<typename T>
vector<T> ordered_union(const vector<T>& v1, const vector<T>& v2)
{
	vector<T> res;
	auto it1 = v1.begin();
	auto it2 = v2.begin();
	while (it1 < v1.end() && it2 < v2.end())
	{
		if (*it1 < *it2)
		{
			res.push_back(*it1);
			it1++;
		}
		else if (*it1 > *it2)
		{
			res.push_back(*it2);
			it2++;
		}
		else
		{
			res.push_back(*it1);
			it1++;
			it2++;
		}
	}
	if (it1 < v1.end())
	{
		res.insert(res.end(), it1, v1.end());
	}
	if (it2 < v2.end())
	{
		std::copy(it2, v2.end(), std::insert_iterator<vector<T>>(res, res.end()));
	}
	return res;
}