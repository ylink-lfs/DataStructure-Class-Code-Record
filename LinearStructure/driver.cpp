#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

double evaluate_infix_expression(const string& str);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string input;
	while (getline(cin, input) && input != "0")
	{
		cout.precision(2);
		cout.setf(ios_base::fixed);
		cout << evaluate_infix_expression(input) << '\n';
	}
	//system("pause");
	return 0;
}

double evaluate_infix_expression(const string& str)
{
	struct expression_term
	{
		char operators;
		int number;
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
		if (isdigit(str[i]))
		{
			int num_len = 1;
			while (i + num_len < str.size() && isdigit(str[i + num_len]))
				num_len++;
			postfix_expression.push_back({ '.', stoi(str.substr(i, num_len)), false });
			i += (num_len - 1);
		}
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
		else
		{
			continue;
		}
	}
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