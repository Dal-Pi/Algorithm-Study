#if 1

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

inline int my_pow(int a) { return a * a; }

struct Road
{
	int C;
	int T;
	vector<int> costMemo;
	Road(int c, int t) : C(c), T(t), costMemo() { costMemo.push_back(0); }
	int getCost(int P) 
	{
		if (P <= T) return 0;
		else
		{
			return C * my_pow(P - T);
			/*
			if ((P - T) == costMemo.size())
			{
				int ret = C * my_pow(P - T);
				costMemo.push_back(ret);
				return ret;
			}
			else
				return costMemo[P - T];
				*/
		}
	}
};

struct Edge
{
	int nCr;
	Road* road;
	Edge(int cr, Road* r) : nCr(cr), road(r) {}
};

struct Crossroad
{
	vector<Edge> edges;
};

bool visited[100001];
vector<Crossroad> crs;
vector<Road*> root;
int maxPerson = 0;
int N = 0, M = 0, K = 0;

void dfs(int nCr, int p)
{
	visited[nCr] = true;
	int targetP = p;
	for (int i = maxPerson; i < p; ++i)
	{
		int sum = 0;
		for (Road* pr : root)
		{
			sum += pr->getCost(i);
		}
		if (sum > K)
		{
			targetP = i - 1;
			break;
		}
		else if (sum == K)
		{
			targetP = i;
			break;
		}
		else
			continue;
	}

	//check case
	if (targetP > maxPerson)
	{
		if (nCr == N)
		{
			maxPerson = targetP;
		}
		else
		{
			for (Edge& edge : crs[nCr].edges)
			{
				if (visited[edge.nCr] == false)
				{
					root.push_back(edge.road);
					dfs(edge.nCr, targetP);
					root.pop_back();
				}
			}
		}
	}

	visited[nCr] = false;
}

void dfsAll()
{
	visited[1] = true;
	for (Edge& edge : crs[1].edges)
	{
		root.push_back(edge.road);
		dfs(edge.nCr, 32623);
		root.pop_back();
	}
}

int main()
{
	cin >> N >> M >> K;

	crs.resize(N+1);

	int A = 0, B = 0, C = 0, T = 0;
	for (int i = 0; i < M; ++i)
	{
		cin >> A >> B >> C >> T;
		Road* road = new Road(C, T);
		crs[A].edges.push_back(Edge(B, road));
		crs[B].edges.push_back(Edge(A, road));
	}

	//dfs
	dfsAll();

	cout << maxPerson << endl;
}




#endif