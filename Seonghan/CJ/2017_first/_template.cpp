#if 0

//template
#include <iostream>
#include <fstream>
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

	}

	fout.close();
	fin.close();
	return 0;
}

#endif