#if 0

#include <iostream>
#include <fstream>
using namespace std;

const string input = "Set1.in";
const string output = "Set1.out";

using longNum = unsigned long long int;

const int countNum = 5;
const unsigned int retDivNum = 1000000007;

longNum pow(int n, int r) {
	longNum ret = 1;
	for (int i = 0; i < r; ++i) {
		ret *= n;
	}
	return ret;
}

longNum getRepeatNum(int d, int r) {
	longNum ret = 0;
	for (int i = 0; i < r; ++i) {
		ret += d * pow(10, i);
	}
	return ret;
}

void setNextRepeatAttr(int* ptr_d, int* ptr_r) {
	if (*ptr_d >= 9) {
		*ptr_d = 1;
		(*ptr_r)++;
	}
	else {
		(*ptr_d)++;
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
		int N[countNum];
		int sumN = 0;
		int S = 0;
		int d = 1;
		int r = 2;
		longNum targetRepNum = 0;

		longNum resultN = 0;

		for (int i = 0; i < countNum; ++i) {
			fin >> N[i];
			sumN += N[i];
		}


		while (true) {
			longNum timesSumN = 0;
			int remainToRepNum = 0;
			int sumPartN = 0;
			targetRepNum = getRepeatNum(d, r);
			bool endFlag = false;

			timesSumN = targetRepNum / sumN;
			remainToRepNum = targetRepNum % sumN;

			int i = 0;
			do {
				if (sumPartN == remainToRepNum) {
					//end case
					resultN = (timesSumN * countNum) + i - 1; // 5n + remain_count
					endFlag = true;
					break;
				}
				else if (sumPartN > remainToRepNum) {
					//continue case, increase repeat number 
					break;
				}
				sumPartN += N[i];
				++i;
			} while (i < countNum);

			if (endFlag) {
				break;
			}
			else {
				//continue case
				setNextRepeatAttr(&d, &r);
				continue;
			}
		}

		fout << resultN % retDivNum << " "
			<< d << "(" << r << ")" << endl;
	}

	fout.close();
	fin.close();
	return 0;
}


#endif