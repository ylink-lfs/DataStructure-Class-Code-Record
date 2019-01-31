#include <utility>
#include "linear_seq.h"

using std::pair;
using std::make_pair;

class ListNode 
{
public:
	int val;
	ListNode* next;
	ListNode(int value, ListNode* next_node = nullptr) : val(value), next(next_node) {}
};

//TextBook Exercise 2.2.(1)
ListNode* unique_merge(ListNode* l1, ListNode* l2)
{	
	auto remove_duplicate = [](ListNode* initial_node) {
		if (!initial_node || initial_node->next)
			return;
		ListNode* prenode = initial_node;
		ListNode* check_node = initial_node->next;
		while (check_node)
		{
			while (check_node && prenode->val == check_node->val)
			{				
				auto tmp = check_node;
				check_node = check_node->next;
				prenode->next = check_node;
				delete tmp;
			}
			prenode = prenode->next;
			check_node = check_node->next;
		}
	};
	remove_duplicate(l1);
	remove_duplicate(l2);


	ListNode* res = new ListNode(0x7fffffff);
	ListNode* it1 = l1;
	ListNode* it2 = l2;
	ListNode* res_it = res;
	while (it1 && it2)
	{
		if (it1->val < it2->val)
		{
			auto tmp = it1;
			it1 = it1->next;
			res_it->next = tmp;
			res_it = res_it->next;
		}
		else if (it1->val > it2->val)
		{
			auto tmp = it2;
			it2 = it2->next;
			res_it->next = tmp;
			res = res_it->next;
		}
		else
		{
			auto tmp = it1;
			auto remove_node = it2;
			it1 = it1->next;
			it2 = it2->next;
			res_it->next = tmp;
			res = res_it->next;
			delete remove_node;
		}
	}
	res_it->next = it1 ? it1 : it2;
	res_it = res;
	res = res->next;
	delete res_it;
	return res;
}

//TextBook Exercise 2.2.(2)
ListNode* descent_merge(ListNode* l1, ListNode* l2)
{
	ListNode* res = new ListNode(0x7fffffff);
	ListNode* it1 = l1;
	ListNode* it2 = l2;
	while (it1 && it2)
	{
		if (it1->val <= it2->val)
		{
			auto tmp = it1;
			it1 = it1->next;
			tmp->next = res->next;
			res->next = tmp;
		}
		else
		{
			auto tmp = it2;
			it2 = it2->next;
			tmp->next = res->next;
			res->next = tmp;
		}
	}
	auto remain_insertion = [&](ListNode* part) {
		ListNode* it = part;
		while (it)
		{
			ListNode* tmp = it;
			it = it->next;
			tmp->next = res->next;
			res->next = tmp;
		}
	};
	remain_insertion(l1 ? l1 : l2);
	ListNode* remove_node = res;
	res = res->next;
	delete remove_node;
	return res;
}

//TextBook Exercise 2.2.(3)
//lista contains the final result
void find_intersection(ListNode* lista, ListNode* listb)
{
	ListNode* headnode = new ListNode(0x7fffffff, lista);
	ListNode* prenode = headnode;
	ListNode* checknode = headnode->next;
	ListNode* listb_iterator = listb;
	auto remove_after = [](ListNode* prenode) {
		ListNode* tmp = prenode->next;
		prenode->next = tmp->next;
		delete tmp;
	};
	while (checknode && listb_iterator)
	{
		if (checknode->val == listb_iterator->val)
		{
			remove_after(prenode);
			checknode = prenode->next;
		}
		else if (checknode->val > listb_iterator->val)
		{
			listb_iterator = listb_iterator->next;
		}
		else
		{
			checknode = checknode->next;
			prenode = prenode->next;
		}
	}
	delete headnode;
}

//TextBook Exercise 2.2.(4)
//Occurs in a but not in b
int find_except(ListNode* la, ListNode* lb)
{
	if (!la)
	{
		return 0;
	}
	else if (!lb)
	{
		ListNode* it = la;
		int cnt = 0;
		while (it)
		{
			it = it->next;
			cnt++;
		}
		return cnt;
	}
	else
	{
		ListNode* headnode = new ListNode(0x7fffffff);
		ListNode* prenode = headnode;
		ListNode* checknode = la;
		ListNode* lb_iterator = lb;
		int cnt = 0;
		auto remove_after = [](ListNode* prenode) {
			ListNode* tmp = prenode->next;
			prenode->next = tmp->next;
			delete tmp;
		};
		while (checknode && lb_iterator)
		{
			if (checknode->val == lb_iterator->val)
			{
				remove_after(prenode);
				checknode = prenode->next;
			}
			else
			{
				lb_iterator = lb_iterator->next;
				checknode = checknode->next;
				prenode = prenode->next;
				cnt++;
			}
		}
		while (checknode)
		{
			checknode = checknode->next;
			cnt++;
		}
		return cnt;
	}
}

//TextBook Exercise 2.2.(5)
//l already has head node
pair<ListNode*, ListNode*> neg_split(ListNode* l)
{
	ListNode* b = new ListNode(0x7fffffff);
	ListNode* c = new ListNode(0x7fffffff);
	ListNode* cur_node = l->next;
	while (cur_node)
	{
		ListNode* tmp = cur_node;
		cur_node = cur_node->next;
		l->next = cur_node;
		if (cur_node->val > 0)
		{			
			tmp->next = c->next;
			c->next = tmp;
		}
		else
		{
			tmp->next = b->next;
			b->next = tmp;
		}
	}
	return make_pair(b, c);
}

//TextBook Exercise 2.2.(6)
ListNode* max_node(ListNode* l)
{
	if (l == nullptr)
		return nullptr;
	ListNode* maxptr = l;
	ListNode* it = l->next;
	while (it)
	{
		if (maxptr->val < it->val)
			maxptr = it;
		it = it->next;
	}
	return maxptr;
}

//TextBook Exercise 2.2.(7)
ListNode* reverse_list(ListNode* l)
{
	if (!l || !(l->next))
		return l;
	ListNode* pre = l;
	ListNode* cur = l->next;
	ListNode* after = l->next->next;
	while (after)
	{
		cur->next = pre;
		pre = cur;
		cur = after;
		after = after->next;
	}
	cur->next = pre;
	l->next = nullptr;
	return cur;
}

//TextBook Exercise 2.2.(8)
void remove_range(ListNode* l, int mink, int maxk)
{
	auto remove_after = [](ListNode* prenode) {
		ListNode* tmp = prenode->next;
		prenode->next = tmp->next;
		delete tmp;
	};
	ListNode* head = new ListNode(0x7fffffff, l);
	ListNode* prenode = head;
	ListNode* checknode = l;
	while (checknode)
	{
		if (checknode->val > mink && checknode->val < maxk)
		{
			remove_after(prenode);
			checknode = prenode->next;
			continue;
		}
		checknode = checknode->next;
		prenode = prenode->next;
	}
	l = head->next;
	delete head;
}

class BiListNode
{
public:
	int val;
	BiListNode* next;
	BiListNode* prior;
	BiListNode(int value, BiListNode* next_node = nullptr, BiListNode* pre_node = nullptr) : 
		val(value), next(next_node), prior(pre_node) {}
};

//TextBook Exercise 2.2.(9)
//It's a fine idea...No flaw
void change(BiListNode* p)
{
	std::swap(p->val, p->prior->val);
}

//TextBook Exercise 2.2.(10)
template<typename T>
void remove_item(sqlist<T>& v, const T& item)
{
	int swap_pos = v.size() - 1;
	int remove_count = 0;
	while (swap_pos >= 0 && swap_pos != sqlist<T>::npos && v[swap_pos] == item)
	{
		swap_pos--;
		remove_count++;
	}
	if (swap_pos == sqlist<T>::npos)
	{
		v.clear();
		return;
	}
	
	int i = swap_pos - 1;
	while (i >= 0 && i != sqlist<T>::npos)
	{
		if (v[i] == item)
		{
			remove_count++;
			std::swap(v[i], v[swap_pos--]);
		}
		else
		{
			i--;
		}
	}
	for (int times = 0; times < remove_count; times++)
	{
		v.erase(v.size() - 1);
	}
}