#if 0

#include <iostream>
#include <fstream>
using namespace std;

const int CM = 30; //using circular memo
const string input = "Set3.in";
const string output = "Set3.out";

int main()
{
	ifstream fin;
	fin.open(input);

	ofstream fout;
	fout.open(output);

	int testcase = 0;
	fin >> testcase;

	for (int T = 0; T < testcase; ++T) {
		int n;
		int k;
		bool avail[CM][10001]; 

		fin >> n;
		fin >> k;

		//pre check case 1
		if ((n > (5 * k)) || (n < k)) {
			fout << "X" << endl;
			continue;
		}

		//pre check case 2
		if (n <= 3) {
			if (n == k)
				fout << "O" << endl;
			else
				fout << "X" << endl;
			continue;
		}

		//init memoization
		//n == 0
		avail[0][0] = true; // n == 0, k == 0
		for (int i = 1; i < CM; ++i) {
			avail[i][0] = false; // if k == 0, always false
		}

		for (int j = 1; j <= k; ++j) {
			avail[0][j] = false; // if n is 0, always false
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= k; ++j) {
				bool result = false;

				if ((i > (5 * j)) || (i < j)) {
					avail[i % CM][j] = false;
					continue;
				}

				if (i >= 1 && j >= 1) {
					result = result || avail[(i - 1) % CM][j - 1];
				}
				if (result) {
					avail[i % CM][j] = true;
					continue;
				}

				if (i >= 4 && j >= 3) {
					result = result || avail[(i - 4) % CM][j - 3];
				}
				if (result) {
					avail[i % CM][j] = true;
					continue;
				}

				if (i >= 5 && j >= 2) {
					result = result || avail[(i - 5) % CM][j - 2];
				}
				if (result) {
					avail[i % CM][j] = true;
					continue;
				}

				if (i >= 9 && j >= 3) {
					result = result || avail[(i - 9) % CM][j - 3];
				}
				if (result) {
					avail[i % CM][j] = true;
					continue;
				}

				if (i >= 10 && j >= 2) {
					result = result || avail[(i - 10) % CM][j - 2];
				}
				if (result) {
					avail[i % CM][j] = true;
					continue;
				}

				avail[i % CM][j] = result;
			}
		}

		if (avail[n % CM][k])
			fout << "O"<< endl;
		else
			fout << "X"<< endl;
	}

	fout.close();
	fin.close();
	return 0;
}

#endif