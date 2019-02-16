#include <stack>
#include <queue>
#include <vector>
#include <forward_list>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

using std::stack;
using std::queue;
using std::vector;
using std::forward_list;
using std::unique_ptr;
using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::isdigit;
using std::abs;

//TextBook Exercise 3.2.(1)
template<typename T>
struct double_stack
{
	int top[2], bot[2];
	unique_ptr<T[]> V;
	int max_elements;
	double_stack(int mx_elements = 100) : V(new T[mx_elements]), max_elements(mx_elements)
	{
		top[0] = bot[0] = -1;
		top[1] = bot[1] = mx_elements;
	}
	bool empty(int which = 0) const { return which ? (top[1] == max_elements) : (top[0] == -1); }
	bool full() const { return top[0] + 1 == top[1]; }
	void push(const T& elem, int which = 0)
	{
		if (which)
		{
			V[--top[1]] = elem;
		}
		else
		{
			V[++top[0]] = elem;
		}
	}
	T at_top(int which = 0) { return which ? V[top[1]] : V[top[0]]; }
	void pop(int which = 0) { which ? top[1]++ : top[0]--; }
};

//TextBook Exercise 3.2.(2)
bool judge_palindrome(const string& str)
{
	for (int i = 0, j = str.size() - 1; i <= j; (i++, j--))
	{
		if (str[i] != str[j])
			return false;
	}
	return true;
}

//TextBook Exercise 3.2.(3)
//No abnormal circumstance with STL stack
void number_into_stack()
{
	stack<int> st;
	int num;
	while (cin >> num)
	{
		if (num != -1)
		{
			st.push(num);
		}
		else
		{
			cout << st.top() << '\n';
			st.pop();
		}
	}
}

//TextBook Exercise 3.2.(4)
//Don't use $ declared in the book, instead just use proper string
//Use space to separate numbers and operators
double evaluate_postfix_expression(const string& str)
{
	//Use stringstream to read "word by word"
	stringstream ist(str);
	string term;
	stack<double> number_stack;
	while (ist >> term)
	{
		//Number case. Use term[1] to handle negative case
		if (isdigit(term[0]) || (term.size() >= 2 && isdigit(term[1])))
		{
			number_stack.push(stod(term));
		}
		else
		{
			char current_operator = term[0];
			double operand2 = number_stack.top();
			number_stack.pop();
			double operand1 = number_stack.top();
			number_stack.pop();
			switch (current_operator)
			{
			case '+':
				number_stack.push(operand1 + operand2);
				break;
			case '-':
				number_stack.push(operand1 - operand2);
				break;
			case '*':
				number_stack.push(operand1 * operand2);
				break;
			case '/':
				number_stack.push(operand1 / operand2);
				break;
			}
		}
	}
	return number_stack.top();
}

//Textbook Exercise 3.2.(5)
//Operations are defined in the textbook
bool stack_operation_validation(const string& str)
{
	int balance_factor = 0;
	for (const auto& single_operation : str)
	{
		switch (single_operation)
		{
		case 'I':
			balance_factor++;
			break;
		case 'O':
			balance_factor--;
			break;
		}
		if (balance_factor < 0)
		{
			return false;
		}
	}
	return balance_factor == 0;
}

//Textbook Exercise 3.2.(6)
//Warning: The following list ADT did not consider resource acquisition
//Didn't use template. Use int as data field
struct list_node 
{
	int val;
	list_node* next;
	list_node(int x, list_node* nxt = nullptr) : val(x), next(nxt) {}
};

//Def of rear: rear->next = hear, then that is rear
struct circulate_linked_list
{
	list_node* head_ptr;
	list_node* rear_ptr;
	circulate_linked_list() : head_ptr(new list_node(0xffffffff, head_ptr)) { rear_ptr = head_ptr; }
	bool empty() const { return head_ptr->next == head_ptr; }
	void clear()
	{
		list_node* it = head_ptr;
		list_node* temp = nullptr;
		while (it->next != head_ptr)
		{
			temp = it;
			it = it->next;
			delete temp;
		}
		delete it;
		head_ptr = new list_node(0xffffffff, head_ptr);
		rear_ptr = head_ptr;
	}
	~circulate_linked_list()
	{
		this->clear();
		delete head_ptr;
	}
};

struct linked_queue
{
	circulate_linked_list list;
	list_node* rear;
	linked_queue() { rear = list.rear_ptr; list.rear_ptr->next = list.head_ptr; }
	bool empty() const { return rear->next == rear; }
	void clear()
	{
		list.clear();
		rear = list.rear_ptr;
		list.rear_ptr->next = list.head_ptr;
	}
	void enqueue(const int x)
	{
		list_node* tmp = new list_node(x, rear->next);
		rear->next = tmp;
		rear = rear->next;
	}
	void dequeue()
	{
		list_node* tmp = rear->next->next;
		rear->next->next = tmp->next;
		delete tmp;
	}
	int front() const
	{
		return rear->next->next->val;
	}
};

//Textbook Exercise 3.2.(7)
//Also use int as element type

//Note that in fact, I reversed the meaning of rear and front.
struct linear_queue
{
	static const int queue_size = 100;
	bool tag;
	int Q[queue_size];
	int frnt, rear;
	int balance_fac;
	linear_queue() : tag(false), frnt(0), rear(0), balance_fac(0) {}
	bool empty() const
	{
		return (frnt == rear) && !tag;
	}
	bool full() const
	{
		return (frnt == rear) && tag;
	}
	void enqueue(const int x)
	{
		balance_fac++;
		tag = true;
		if (++frnt >= queue_size)
			frnt = 0;
		Q[frnt] = x;
	}
	int front() const
	{
		return Q[frnt];
	}
	void dequeue()
	{
		balance_fac--;
		if (++rear >= queue_size)
			rear = 0;
		if (rear == frnt)
			tag = false;
	}
};

//Textbook Exercise 3.2.(8)
//Check the answer
struct bidirectional_queue
{
	static const int queue_size = 100;
	int Q[queue_size];
	int frnt, rear;
	int balance_fac;
	bidirectional_queue() : frnt(0), rear(0), balance_fac(0) {}
	bool full() const { return balance_fac >= queue_size - 1; }
	bool empty() const { return frnt == rear; }
	void push_front(const int x)
	{
		balance_fac++;
		frnt++;
		if (frnt >= queue_size)
			frnt = 0;
		Q[frnt] = x;
	}
	void push_back(const int x)
	{
		balance_fac++;
		rear--;
		if (rear < 0)
			frnt = queue_size - 1;
		Q[rear] = x;
	}
	void pop_back()
	{
		balance_fac--;
		rear++;
		if (rear >= queue_size)
			rear = 0;
	}
	void pop_front()
	{
		balance_fac--;
		frnt--;
		if (frnt < 0)
			frnt = queue_size - 1;
	}
};

//Textbook Exercise 3.2.(9)
/*
Ack(2, 1) = Ack(1, Ack(2, 0)) = Ack(1, 3) = Ack(0, Ack(1, 2)) = Ack(0, 4) = 5
												   Ack(1, 2) = Ack(0, Ack(1, 1)) = Ack(0, 3) = 4
				   Ack(2, 0) = Ack(1, 1) = Ack(0, Ack(1, 0)) = Ack(0, 2) = 3
												  Ack(1, 0) = Ack(0, 1) = 2
*/
int Ack(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return Ack(m - 1, 1);
	else
		return Ack(m - 1, Ack(m, n - 1));
}

int Ack_nonrc(int m, int n)
{
	int akm[100][100];
	for (int j = 0; j < 100; j++)
	{
		akm[0][j] = j + 1;
	}
	for (int i = 1; i <= m; i++)
	{
		akm[i][0] = akm[i - 1][1];
		for (int j = 1; j <= n; j++)
		{
			akm[i][j] = akm[i - 1][akm[i][j - 1]];
		}
	}
	return akm[m][n];
}

//Textbook Exercise 3.2.(10)
void maxval(int& cur_max, list_node* head)
{
	if (!head)
		return;
	else
	{
		if (cur_max < head->val)
			cur_max = head->val;
		maxval(cur_max, head->next);
	}
}
int maxval(list_node* p)
{
	if (!p->next)
		return p->val;
	else
	{
		int maxv = maxval(p->next);
		return p->val > maxv ? p->val : maxv;
	}
}

int node_count(list_node* head)
{
	if (!head)
		return 0;
	else
		return 1 + node_count(head->next);
}

void node_avg(list_node* head, int& depth,double& cur_num)
{
	if (!head)
	{
		cur_num /= depth;
	}
	else
	{
		depth++;
		cur_num += head->val;
		node_avg(head->next, depth, cur_num);
	}
}
double node_avg(list_node* p, int n)
{
	if (!p->next)
		return p->val;
	else
	{
		double ave = node_avg(p->next, n - 1);
		return (ave * (n - 1) + p->val) / n;
	}
}