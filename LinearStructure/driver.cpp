#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

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

int main(void)
{
	linked_queue q;
	for (int i = 0; i < 4; i++)
	{
		q.enqueue(i);
		cout << q.front() << '\n';
	}
	for (int i = 0; i < 4; i++)
	{
		cout << q.front() << '\n';
		q.dequeue();
	}
	system("pause");
	return 0;
}

