#include <iostream>
#include "linear_seq.h"
#include "linear_linked.h"
#include "application.h"

using namespace std;

int main(void)
{
	vector<int> list1({ 3, 5, 8, 11 });
	vector<int> list2({ 2, 6, 8, 9, 11, 15, 20 });
	vector<int> res(ordered_union(list1, list2));
	
	for (auto elem : res)
	{
		cout << elem << ' ';
	}
	cout << endl;
	system("pause");
	return 0;
}