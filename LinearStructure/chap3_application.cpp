//Chap 3 Section 6
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>

using std::string;
using std::vector;
using std::stack;
using std::map;
using std::set;
using std::pair;
using std::make_pair;
using std::to_string;

//3.6.1, decimal convertor
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

string decimal_convertor(const string& input, int radix)
{
	return actual_convertor(input, radix);
}

//3.6.2, parentheses check
bool check_parentheses(const string& str)
{
	stack<char> st;
	map<char, char> matched_parentheses({
		pair<char, char>(')', '('),
		pair<char, char>('}', '{'),
		pair<char, char>(']', '[')
		});
	set<char> exist_parentheses({ '(', '{', '[' });
	for (const auto& elem : str)
	{
		//Left half of the parentheses
		if (exist_parentheses.find(elem) != exist_parentheses.end())
		{
			st.push(elem);
		}
		//Right half of the parentheses
		else if (matched_parentheses.find(elem) != matched_parentheses.end())
		{
			//Single right half or just doesn't match
			if (st.empty() || matched_parentheses[elem] != st.top())
			{
				return false;
			}
			//One matched parentheses
			else
			{
				st.pop();
			}
		}
		//Other characters
		else
		{
			continue;
		}
	}
	//If the stack is empty now, then all parentheses match successfully
	return st.empty();
}