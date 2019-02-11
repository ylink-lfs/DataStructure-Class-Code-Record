#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

int count_move = 0;

void haoni(int plate_count);
void haoni(int plate_id, char mv_from, char mv_to, char assist);

int main(void)
{
	ios_base::sync_with_stdio(false);
	haoni(11);
	system("pause");
	return 0;
}

void haoni(int plate_count)
{
	count_move = 0;
	haoni(plate_count, 'A', 'C', 'B');
}

//From mv_from to mv_to via assist
void haoni(int plate_id, char mv_from, char mv_to, char assist)
{
	if (plate_id == 1)
	{
		cout << ++count_move << " Times move: From " << mv_from << " move ID " << 1 << " to " 
			<< mv_to << '\n';
	}
	else
	{
		haoni(plate_id - 1, mv_from, assist, mv_to);
		cout << ++count_move << " Times move: From " << mv_from << " move ID " << plate_id << " to "
			<< mv_to << '\n';
		haoni(plate_id - 1, assist, mv_to, mv_from);
	}
}