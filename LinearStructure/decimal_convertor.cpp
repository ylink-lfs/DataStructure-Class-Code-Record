#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

//Convert a decimal to number of other radix
string decimal_convertor(const string& input, int radix = 8);
string actual_convertor(string str, int radix = 8);

int main(void)
{
	string digit_input;
	while (cin >> digit_input)
	{
		cout << decimal_convertor(digit_input) << endl;
	}
	system("pause");
	return 0;
}

string decimal_convertor(const string& input, int radix)
{
	return actual_convertor(input, radix);
}

string actual_convertor(string str, int radix)
{
	int num = stoi(str);
	if (num < radix)
	{
		return to_string(num);
	}
	else
	{
		return actual_convertor(to_string(num / radix), radix) + to_string(num % radix);
	}
}