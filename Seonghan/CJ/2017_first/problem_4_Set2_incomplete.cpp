#if 0

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const string input = "Set2.in";
const string output = "Set2.out";

const int countNum = 5;
const unsigned int retDivNum = 1000000007;

using veryLong = unsigned long long;
class BigInt {
public:
	const static int WIDTH = 100000;
	const static int MAX = 1000;
	BigInt() {
		for (int i = 0; i < MAX; ++i)
			nums[i] = 0;
	}
	BigInt(const BigInt& rhs) {
		for (int i = 0; i < MAX; ++i) {
			nums[i] = rhs.nums[i];
		}
	}
	BigInt& operator=(const BigInt& rhs) {
		for (int i = 0; i < MAX; ++i) {
			nums[i] = rhs.nums[i];
		}
		return *this;
	}

	BigInt& operator +(int src) {
		int up = src;
		for (int i = 0; i < MAX; ++i) {
			if (up == 0)
				continue;
			nums[i] += up;
			if (nums[i] >= WIDTH) {
				up = nums[i] / WIDTH;
				nums[i] %= WIDTH;
			}
			else
				up = 0;
		}
		return *this;
	}
	BigInt& operator +(const BigInt& src) {
		int up = 0;
		for (int i = 0; i < MAX; ++i) {
			if (nums[i] == 0 && src.nums[i] == 0 && up == 0)
				break;
			nums[i] += src.nums[i] + up;
			if (nums[i] >= WIDTH) {
				up = nums[i] / WIDTH;
				nums[i] %= WIDTH;
			}
			else
				up = 0;
		}
		return *this;
	}
	BigInt& operator -(int src) {
		//src is absolutely lower than this
		int down = src;
		for (int i = 0; i < MAX; ++i) {
			if (down == 0)
				break;
			nums[i] -= down % WIDTH;
			if (nums[i] < 0) {
				nums[i] += WIDTH;
				nums[i + 1]--;
			}
			down /= WIDTH;
		}
		return *this;
	}
	BigInt& operator *(int src) {
		veryLong up = 0;
		int i;
		for (i = 0; i < MAX; ++i) {
			if (nums[i] == 0 && up == 0)
				continue;
			nums[i] = nums[i] * src + up;
			up = nums[i] / WIDTH;
			if (nums[i] >= WIDTH)
				nums[i] %= WIDTH;
		}
		return *this;
	}
	BigInt operator /(int src) {
		BigInt ret;
		int remain = 0;
		for (int i = MAX - 1; i >= 0; --i) {
			ret.nums[i] = nums[i] + remain;
			remain = (ret.nums[i] % src) * WIDTH;
			ret.nums[i] /= src;
		}
		return ret;
	}
	veryLong operator %(int src) {
		veryLong remain = 0;
		for (int i = MAX - 1; i >= 0; --i) {
			veryLong target = nums[i];
			target += remain;
			if (i != 0)
				remain = (target % src) * WIDTH;
			else
				remain = (target % src);
		}
		return remain;
	}
	void printNum() {
		int start = 0;
		for (int i = MAX - 1; i >= 0; --i)
			if (nums[i] != 0) {
				start = i;
				break;
			}
		for (int i = start; i >= 0; --i)
			if (i == start)
				cout << setfill(' ') << nums[i];
			else
				cout << setw(5) << setfill('0') << nums[i];
	}
private:
	veryLong nums[MAX + 1];
};

using longNum = BigInt;

longNum pow(int n, int r) {
	longNum ret;
	ret = ret + 1;
	for (int i = 0; i < r; ++i) {
		ret = ret * n;
	}
	return ret;
}


longNum getRepeatNum(int d, int r) {
	longNum ret;
	for (int i = 0; i < r; ++i) {
		ret = ret + (pow(10, i) * d);
	}

	/*
	ret.printNum();
	cout << endl;
	*/
	return ret;
}

void getRepeatNum_alter(longNum& num, int d) {
	if (d == 1) {
		num = num / 9;
		num = num * 10;
		num = num + 1;
	}
	else {
		num = num / (d - 1);
		num = num * d;
	}

	
	num.printNum();
	cout << endl;
	
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
		longNum targetRepNum;

		//test
		targetRepNum = targetRepNum + 9;
		//test

		longNum resultN;

		cout << "start : " << __TIME__ <<endl;

		for (int i = 0; i < countNum; ++i) {
			fin >> N[i];
			sumN += N[i];
		}


		while (true) {
			longNum timesSumN;
			int remainToRepNum = 0;
			int sumPartN = 0;
			//test
			//targetRepNum = getRepeatNum(d, r);
			getRepeatNum_alter(targetRepNum, d);
			//test
			bool endFlag = false;

			remainToRepNum = targetRepNum % sumN;

			int i = 0;
			do {
				if (sumPartN == remainToRepNum) {
					//end case
					timesSumN = targetRepNum / sumN;
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


		cout << resultN % retDivNum << " "
			<< d << "(" << r << ")" << endl;

		fout << resultN % retDivNum << " "
			<< d << "(" << r << ")" << endl;
	}

	fout.close();
	fin.close();
	return 0;
}

#endif