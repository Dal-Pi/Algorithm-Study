#if 1

#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

using COST_TYPE = long long;
inline COST_TYPE my_pow(int a) { return a * a; }

struct Road
{
	COST_TYPE cost;
	int C;
	int T;
	Road(int c, int t) : cost(0), C(c), T(t) {}
	void setCost(int P)
	{
		if (P <= T)
			cost = 0;
		else
			cost = C * my_pow(P - T);
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
	int num;
	vector<Edge> edges;
	Crossroad(int n) : num(n), edges() {}
};

bool visited[100001];
vector<Crossroad> crs;
vector<Road*> roads;
int maxPerson = 0;
int N = 0, M = 0, K = 0;
const COST_TYPE MAX_COST = LLONG_MAX;

vector<COST_TYPE> dijkstra(int nCr)
{
	vector<COST_TYPE> costs(N + 1, MAX_COST);
	costs[nCr] = 0;
	priority_queue<pair<COST_TYPE, Crossroad*>> pq;

	pq.push(make_pair(0, &crs[nCr]));

	while (pq.empty() == false)
	{
		COST_TYPE cost = -pq.top().first;
		Crossroad* cr = pq.top().second;
		pq.pop();

		if (costs[cr->num] < cost) continue;
		if (cost > K) break;

		for (Edge& edge : cr->edges)
		{
			int nextCr = edge.nCr;
			COST_TYPE nextCost = cost + (edge.road)->cost;

			if (costs[nextCr] > nextCost)
			{
				costs[nextCr] = nextCost;
				pq.push(make_pair(-nextCost, &crs[nextCr]));
			}
		}
	}
	return costs;
}

int main()
{
	cin >> N >> M >> K;

	crs.push_back(Crossroad(0));
	for (int i = 1; i <= N; ++i)
	{
		crs.push_back(Crossroad(i));
	}

	int A = 0, B = 0, C = 0, T = 0;
	for (int i = 0; i < M; ++i)
	{
		cin >> A >> B >> C >> T;
		Road* road = new Road(C, T);
		roads.push_back(road);
		crs[A].edges.push_back(Edge(B, road));
		crs[B].edges.push_back(Edge(A, road));
	}

	int start = 0;
	int end = 32768; // 32623

	int prevStart = -1;
	int prevEnd = -1;

	while ((prevStart != start) || (prevEnd != end))
	{
		int mid = (start + end) / 2;
		for (Road* road : roads)
			road->setCost(mid);

		vector<COST_TYPE> costs = dijkstra(1);

		prevStart = start;
		prevEnd = end;

		if (costs[N] > K)
			end = mid;
		else
			start = mid;
	}

	//check which is result
	for (Road* road : roads)
		road->setCost(end);
	vector<COST_TYPE> costs_end = dijkstra(1);
	if (costs_end[N] > K)
		cout << start << endl;
	else
		cout << end << endl;

	return 0;
}

#endif