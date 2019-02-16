#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <set>
#include <cctype>

using namespace std;

int Ack(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return Ack(m - 1, 1);
	else
		return Ack(m - 1, Ack(m, n - 1));
}

int main(void)
{
	cout << Ack(2, 1) << '\n';
	system("pause");
	return 0;
}

