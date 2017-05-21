#if 0

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const string input = "Set1.in";
const string output = "Set1.out";

int main() {
	ifstream fin;
	fin.open(input);

	ofstream fout;
	fout.open(output);

	int testcase = 0;
	fin >> testcase;

	for (int T = 0; T < testcase; ++T) {
		int N[5];
		int sumN = 0;
		
		for (int i = 0; i < 5; ++i) {
			fin >> N[i];
		}


		
		for (int i = 0; i < 1000; ++i) {
			sumN += N[i % 5];

			cout << setw(15) << N[i % 5];
			cout << setw(15) << sumN << endl;
		}

		
	}

	fout.close();
	fin.close();
	return 0;
}

#endif