#if 0

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Tower
{
	int bottom;
	int height;
	Tower(int init) : bottom(init), height(1) {}
	void insert(int cube)
	{
		bottom = cube;
		height++;
	}
};

int main()
{
	int N;
	cin >> N;
	vector<int> cubes(N);

	for (int i = 0; i < N; ++i)
		cin >> cubes[i];

	sort(begin(cubes), end(cubes), [](int a, int b) -> bool { return a < b; });

	vector<Tower> towers;
	for (int cube : cubes)
	{
		int curTowerCnt = towers.size();
		bool inserted = false;
		for (Tower& tower : towers)
		{
			if (tower.height <= cube)
			{
				tower.insert(cube);
				inserted = true;
				break;
			}
		}
		if (inserted == false)
		{
			towers.push_back(Tower(cube));
		}
	}

	cout << towers.size() << endl;
}


#endif