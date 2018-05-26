#if 0

#include <iostream>
#include <string>
using namespace std;

struct direction
{
	int xDir;
	int yDir;
};
direction dirs[8] = {
	{ -1, -1 },
	{  0, -1 },
	{  1, -1 },
	{ -1,  0 },
	{  1,  0 },
	{ -1,  1 },
	{  0,  1 },
	{  1,  1 }
};

string str;
char map[100][100];
int cnt[100];
bool result = false;
int N = 0, M = 0;

inline int my_abs(int num) { num > 0 ? num : -num; }

bool search_eachway(int x, int y, int pos, int dirIdx)
{
	if (str[pos] != map[y][x])
		return false;
	else
	{
		if (str.length() == (pos + 1))
		{
			result = true;
			return true;
		}
			
		else
			return search_eachway(x + dirs[dirIdx].xDir, y + dirs[dirIdx].yDir, pos + 1, dirIdx);
	}
}


void search(int x, int y)
{
	for (int i = 0; i < 8; ++i)
	{
		//endcase2 : length check
		int length = str.length();
		if (dirs[i].xDir == -1 && length > (x + 1)) continue;
		if (dirs[i].yDir == -1 && length > (y + 1)) continue;
		if (dirs[i].xDir == 1 && length > (M - x)) continue;
		if (dirs[i].yDir == 1 && length > (N - y)) continue;

		//endcase3 : search result
		if (search_eachway(x, y, 0, i))
			return;
	}
}

int main()
{
	cin >> str;
	cin >> N >> M;

	for (int i = 'A'; i < 'Z'; ++i)
		cnt[i] = 0;

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			char target;
			cin >> target;
			cnt[target]++;
			map[i][j] = target;
		}
	}

	//endcase 1 : count check
	for (int i = 0; i < str.length(); ++i)
	{
		if (cnt[str[i]] == 0)
		{
			cout << 0 << endl;
			return 0;
		}
	}

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (map[i][j] == str[0])
			{
				search(j, i);
			}
		}
	}

	cout << result << endl;
	return 0;
}


#endif