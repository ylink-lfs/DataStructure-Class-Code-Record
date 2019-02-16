#include <iostream>
#include "linear_seq.h"
#include "linear_linked.h"
#include "prac_stack.h"
#include "prac_queue.h"

using namespace std;

bool check_parentheses(const string& str);

int main(void)
{
	string input("(()]");
	if (check_parentheses(input))
	{
		cout << "Parentheses match successfully.\n";
	}
	else
	{
		cout << "Match failed.\n";
	}

	system("pause");
	return 0;
}