#if 0

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const string input = "Set3.in";
const string output = "Set3.out";

const int minLen = 0;

int max(int a, int b) {
	return a > b ? a : b;
}

int getMinR(int left, int right) {
	int distance = right - left;
	if (distance % 2 == 1) {
		return (distance / 2) + 1;
	}
	else {
		return distance / 2;
	}
}

int main() {
	ifstream fin;
	fin.open(input);

	ofstream fout;
	fout.open(output);

	int testcase = 0;
	fin >> testcase;

	for (int T = 0; T < testcase; ++T) {
		int N;
		int p[100001];
		int result;

		result = minLen;
		fin >> N;
		for (int i = 0; i < N; ++i) {
			fin >> p[i];
		}

		//pre check case
		if (N == 1) {
			fout << 0 << endl;
			continue;
		}


		sort(p, p + N);

		result = max(result, getMinR(p[0], p[1]));

		for (int i = 0; i < N - 2; ++i) {
			result = max(result, getMinR(p[i], p[i + 2]));
		}

		result = max(result, getMinR(p[N - 2], p[N - 1]));

		fout << result << endl;
	}

	fout.close();
	fin.close();
	return 0;
}

#endif