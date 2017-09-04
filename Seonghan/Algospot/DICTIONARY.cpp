#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<bool>> adj;
vector<string> words;
vector<bool> visited;
vector<int> order;

void dfs(int here) {
	visited[here] = true;
	for (int there = 0; there < adj.size(); ++there) {
		if (adj[here][there] && visited[there] == false) {
			dfs(there);
		}
	}
	order.push_back(here);
}

vector<int> getOrder() {
	visited = vector<bool>(adj.size(), false);

	for (int i = 0; i < adj.size(); ++i) {
		if (visited[i] == false) {
			dfs(i);
		}
	}
	reverse(order.begin(), order.end());

	for (int i = 0; i < adj.size() - 1; ++i) {
		for (int j = i + 1; j < adj.size(); ++j) {
			if (adj[order[j]][order[i]]) {
				return vector<int>();
			}
		}
	}
	return order;
}

int main() {
	

	int C = 0;
	cin >> C;
	for (int tc = 0; tc < C; ++tc) {
		adj = vector<vector<bool>>(26, vector<bool>(26, false));
		words.clear();
		order.clear();

		int N = 0;
		cin >> N;
		string word;
		for (int i = 0; i < N; ++i) {
			cin >> word;
			words.push_back(word);
		}

		for (int i = 0; i < N - 1; ++i) {
			string prev = words[i];
			string next = words[i + 1];
			int minLength = prev.length() < next.length() ? prev.length() : next.length();
			for (int j = 0; j < minLength; ++j) {
				if (prev[j] != next[j]) {
					adj[prev[j] - 'a'][next[j] - 'a'] = true;
					break;
				}
			}
		}

		vector<int> result = getOrder();

		if (result.size() == 0) {
			cout << "INVALID HYPOTHESIS" << endl;
		}
		else {
			for (int i = 0; i < result.size(); ++i) {
				cout << static_cast<char>(result[i] + 'a');
			}
			cout << endl;
		}
		
	}
}