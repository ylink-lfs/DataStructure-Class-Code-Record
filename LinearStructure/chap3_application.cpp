//Chap 3 Section 6
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <cctype>
#include <climits>

using std::string;
using std::vector;
using std::stack;
using std::map;
using std::unordered_map;
using std::set;
using std::pair;
using std::make_pair;
using std::to_string;
using std::isdigit;
using std::ispunct;

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

//3.6.3, evaluate infix expression
//Support float number elementary arithmatic
double evaluate_infix_expression(const string& str)
{
	if(!check_parentheses(str))
	{
		std::cerr << "Invalid infix expression.";
		return DBL_MIN;
	}
	struct expression_term
	{
		char operators;
		double number;
		bool is_operator;
	};
	unordered_map<char, int> support_operators({
		pair<char, int>('+', 1),
		pair<char, int>('-', 1),
		pair<char, int>('*', 2),
		pair<char, int>('/', 2),
		});

	//Generate postfix expression
	vector<expression_term> postfix_expression;
	stack<char> assist_stack;
	for (int i = 0; i < str.size(); i++)
	{
		//Digit term
		if (isdigit(str[i]))
		{
			int num_len = 1;
			//Consider number with dot
			while (i + num_len < str.size() && (isdigit(str[i + num_len]) || str[i + num_len] == '.'))
				num_len++;
			//7 is dummy number, change it freely
			postfix_expression.push_back({ static_cast<char>(7), stoi(str.substr(i, num_len)), false });
			i += (num_len - 1);
		}

		//Operator, fxxking ()...
		else if (support_operators.find(str[i]) != support_operators.end() ||
			str[i] == '(' || str[i] == ')')
		{
			char current_operator = str[i];
			if (assist_stack.empty() ||
				support_operators[assist_stack.top()] < support_operators[current_operator] ||
				current_operator == '(')
			{
				assist_stack.push(current_operator);
			}
			else
			{
				while (!assist_stack.empty() &&
					(support_operators[assist_stack.top()] >= support_operators[current_operator] ||
						current_operator == ')'))
				{
					if (assist_stack.top() == '(' && current_operator == ')')
					{
						assist_stack.pop();
						break;
					}
					postfix_expression.push_back({ assist_stack.top(), -1, true });
					assist_stack.pop();
				}
				if (current_operator != ')')
					assist_stack.push(current_operator);
			}
		}
		//Other characters
		else
		{
			std::cerr << "Invalid infix expression.";
			return DBL_MIN;
		}
	}
	//Let out the rest operators
	while (!assist_stack.empty())
	{
		postfix_expression.push_back({ assist_stack.top(), -1, true });
		assist_stack.pop();
	}

	//Use postfix expression to evaluate value
	stack<double> st;
	for (const auto& elem : postfix_expression)
	{
		if (elem.is_operator)
		{
			//Note that operand2 is at front
			double operand2 = st.top();
			st.pop();
			double operand1 = st.top();
			st.pop();
			char current_operator = elem.operators;
			switch (current_operator)
			{
			case '+':
				st.push(operand1 + operand2);
				break;
			case '-':
				st.push(operand1 - operand2);
				break;
			case '*':
				st.push(operand1 * operand2);
				break;
			case '/':
				st.push(operand1 / operand2);
				break;
			}
		}
		else
		{
			st.push(elem.number);
		}
	}
	return st.top();
}