//Chap 2 Section 8, polynomial addition and multiplication
#include <list>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct polynominal_term
{
	int exponent;
	int factor;
	polynominal_term(const int exp, const int fact) : exponent(exp), factor(fact) {}
	friend ostream& operator<<(ostream& os, const polynominal_term& term)
	{
		return os << term.exponent << ' ' << term.factor;
	}
};

using polynominal = list<polynominal_term>;

polynominal add_polynominal(const polynominal& p1, const polynominal& p2);
polynominal multiply_polynominal(const polynominal& p1, const polynominal& p2);
polynominal one_term_multiply(const polynominal_term& term, const polynominal& p);
void read_polynominal(polynominal& p, int term_num, istream& ist = cin);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int max_exp1, max_exp2;
	while (cin >> max_exp1 >> max_exp2)
	{
		polynominal p1;
		read_polynominal(p1, max_exp1 + 1);
		polynominal p2;
		read_polynominal(p2, max_exp2 + 1);
		polynominal res = multiply_polynominal(p1, p2);
		for (auto it = res.begin(); it != res.end(); it++)
		{
			cout << it->factor;
			auto assist_it = it;
			assist_it++;
			if (assist_it == res.end())
			{
				if (res.size() < max_exp1 + max_exp2 + 1)
				{
					for (int j = 0; j < max_exp1 + max_exp2 - it->exponent; j++)
					{
						cout << ' ' << 0;
					}
				}
				cout << '\n';
			}
			else
			{
				if (it->exponent + 1 != assist_it->exponent)
				{
					for (int i = 0; i < assist_it->exponent - it->exponent - 1; i++)
					{
						cout << ' ' << 0;
					}
				}
				cout << ' ';
			}
		}
		
	}
	return 0;
}

polynominal add_polynominal(const polynominal& p1, const polynominal& p2)
{
	polynominal poly;
	auto it1 = p1.begin();
	auto it2 = p2.begin();
	while (it1 != p1.end() && it2 != p2.end())
	{
		if (it1->exponent < it2->exponent)
		{
			poly.push_back(*it1++);
		}
		else if (it1->exponent > it2->exponent)
		{
			poly.push_back(*it2++);
		}
		else
		{
			if (it1->factor + it2->factor != 0)
			{
				poly.push_back(polynominal_term(it1->exponent, it1->factor + it2->factor));
			}
			it1++;
			it2++;
		}
	}
	if (it1 != p1.end())
	{
		while (it1 != p1.end())
		{
			poly.push_back(*it1++);
		}
	}
	else if (it2 != p2.end())
	{
		while (it2 != p2.end())
		{
			poly.push_back(*it2++);
		}
	}
	return poly;
}

polynominal multiply_polynominal(const polynominal& p1, const polynominal& p2)
{
	vector<polynominal> term_mul_res;
	for (const auto& tm : p1)
	{
		term_mul_res.push_back(one_term_multiply(tm, p2));
	}
	polynominal res;
	res.push_back(polynominal_term(0, 0));
	for (const auto& tm : term_mul_res)
	{
		res = add_polynominal(res, tm);
	}
	return res;
}

polynominal one_term_multiply(const polynominal_term& term, const polynominal& p)
{
	polynominal res(p);
	for (auto& one_term : res)
	{
		one_term.exponent += term.exponent;
		one_term.factor *= term.factor;
	}
	return res;
}

void read_polynominal(polynominal& p, int term_num, istream& ist)
{
	if (!p.empty())
	{
		p.clear();
	}
	
	for (int i = 0; i < term_num; i++)
	{
		int fac;
		ist >> fac;
		if(fac)
			p.push_back(polynominal_term(i, fac));
	}
}
