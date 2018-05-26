#if 0


#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Block
{
	int height;
	int prev;
	int next;
};

struct BlockChain
{
	int min; //origin pos
	int max; //origin pos
	BlockChain(int pos) : min(pos), max(pos) {}
	void insert(int pos)
	{
		min = pos < min ? pos : min;
		max = pos > max ? pos : max;
	}
};

int main()
{
	int N = 0;
	cin >> N;

	int input;
	vector<int> heightSeq;
	Block blocks[1001];
	map<int, BlockChain*> blockMap;
	for (int i = 0; i < N; ++i)
	{
		cin >> input;
		blocks[i].height = input;
		blocks[i].prev = i - 1;
		blocks[i].next = i + 1;

		heightSeq.push_back(input);

		//check point
		blockMap[input] = new BlockChain(i);
	}

	sort(begin(heightSeq), end(heightSeq), [](int a, int b) -> bool { return a < b; });


	int curPos = 0;
	int instCnt = 0;
	for (int i = 0; i < heightSeq.size(); ++i)
	{
		int targetPos = blockMap[heightSeq[i]]->min; // check point
		//move to target
		if (curPos < targetPos)
		{
			while (curPos != targetPos)
			{
				curPos = blocks[curPos].next;
				instCnt++;
			}
		}
		else if (curPos > targetPos)
		{
			while (curPos != targetPos)
			{
				curPos = blocks[curPos].prev;
				instCnt++;
			}
		}
		//else do not move 

		//delete
		if (blocks[curPos].prev == -1)
		{
			int nextPos = blocks[curPos].next;
			blocks[nextPos].prev = -1;
		}
		else if (blocks[curPos].next == N)
		{
			int prevPos = blocks[curPos].prev;
			blocks[prevPos].next = N;
		}
		else
		{
			int nextPos = blocks[curPos].next;
			int prevPos = blocks[curPos].prev;
			blocks[nextPos].prev = blocks[curPos].prev;
			blocks[prevPos].next = blocks[curPos].next;
		}
	}

	cout << instCnt + 1 << endl;

	map<int, BlockChain*>::iterator it;
	for (it = begin(blockMap); it != end(blockMap); ++it)
	{
		delete (*it).second;
	}

	return 0;
}

#endif
