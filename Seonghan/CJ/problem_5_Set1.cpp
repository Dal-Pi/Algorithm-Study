
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define MY_DEBUG

#ifdef MY_DEBUG
#include <iomanip>
#endif

using namespace std;

const string input = "Set1.in";
const string output = "Set1.out";

const int retDivNum = 1000000007;
const int MAX_N = 10000001;

const double PI = 2.0 * acos(0.0);

struct MyVector {
	double x, y;

	explicit MyVector(double _x, double _y) : x(_x), y(_y) {}
	bool operator == (const MyVector& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const MyVector& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	MyVector operator + (const MyVector& rhs) const {
		return MyVector(x + rhs.x, y + rhs.y);
	}
	MyVector operator - (const MyVector& rhs) const {
		return MyVector(x - rhs.x, y - rhs.y);
	}
	MyVector operator * (double rhs) const {
		return MyVector(x * rhs, y * rhs);
	}
	double norm() const { return hypot(x, y); }
	MyVector normalize() const {
		return MyVector(x / norm(), y / norm());
	}
	double dot(const MyVector& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const MyVector& rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	MyVector project(const MyVector& rhs) const {
		MyVector r = rhs.normalize();
		return r * r.dot(*this);
	}
};

struct LightHouse {
	MyVector vector; //vector to next lighthouse
	int number;
	int right; //clock direction
	int left; 
	int shelter; //longest distance with right lighthouse
	bool isEdge; // not used yet

	explicit LightHouse(int _x, int _y, int num)
		: vector(static_cast<double>(_x), static_cast<double>(_y)), number(num), shelter(0), isEdge(false)
	{
	}

	void setRight(LightHouse* rhs) {
		right = rhs->number;
		rhs->left = number;
	}
};

double ccw(const MyVector& a, const MyVector& b) {
	return a.cross(b);
}
double ccw(const MyVector& p, const MyVector& a, const MyVector& b) {
	return ccw(a - p, b - p);
}

MyVector perpendicularFoot(const MyVector& p, const MyVector& a, const MyVector& b) {
	return a + (p - a).project(b - a);
}

double pointToLine(const MyVector& p, const MyVector& a, const MyVector& b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}

void lightHouseNumSort(int* a, int* b) {
	if (*a > *b) {
		int temp = *b;
		*b = *a;
		*a = temp;
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
		int n = 0;
		int k = 0; //maximum 2n
		int m = 0; //maximum n
#ifdef MY_DEBUG
		int map[502][502];
		for (int i = 0; i < 501; ++i)
			for (int j = 0; j < 501; ++j)
				map[i][j] = -1;
#endif
		vector<LightHouse*> lhAll;
		vector<LightHouse*> lhEdge;
		LightHouse* lhMax = new LightHouse(MAX_N, MAX_N, -1);
		LightHouse* lhStart = lhMax;

		fin >> n;
		fin >> k;
		fin >> m;

		for (int i = 0; i < k; ++i) {
			//input lighthouse position
			int x = 0, y = 0;
			
			fin >> x >> y;

			LightHouse* lh = new LightHouse(x, y, i + 1);
#ifdef MY_DEBUG
			map[y][x] = i + 1;
#endif
			lhAll.push_back(lh);

			if (lh->vector < lhStart->vector)
				lhStart = lh;
		}

		lhStart->isEdge = true;
		lhEdge.push_back(lhStart);
		vector<LightHouse*>::iterator it;
		LightHouse* lhFrom;
		LightHouse* lhNext;
		while (true) {
			it = lhAll.begin();
			lhFrom = lhEdge.back();
			lhNext = *it;
			it++;
			//find edge and shelter
			for (; it != lhAll.end(); ++it) {
				double crossDiff = ccw(lhFrom->vector, lhNext->vector, (*it)->vector);
				double distDiff = (lhNext->vector - lhFrom->vector).norm()
					- ((*it)->vector - lhFrom->vector).norm();
				if (crossDiff > 0 || (crossDiff == 0 && distDiff < 0)) {
					lhNext = *it;
				}
			}

			//find end case
			if (lhStart == lhNext)
				break;

			//save
			lhNext->isEdge = true;
			lhFrom->setRight(lhNext);
			lhEdge.push_back(lhNext);
		}
		lhEdge.back()->setRight(lhEdge.front());

		
		//calc shelter distance
		//vector<LightHouse*>::iterator edgeIt;
		//for (edgeIt = lhEdge.begin(); edgeIt != lhEdge.end(); ++edgeIt) {
		for (int i = 0; i < lhEdge.size(); ++i) {
			double longestDist = 0;
			int longestShelterNum = lhEdge[i]->number; // me
			for (int j = 0; j < lhAll.size(); ++j) {
				double dist = pointToLine(lhAll[j]->vector,
					lhEdge[i]->vector, lhAll[lhEdge[i]->right - 1]->vector);
				if (dist > longestDist) {
					longestDist = dist;
					longestShelterNum = lhAll[j]->number;
				}
				else if (dist == longestDist) {
#ifdef MY_DEBUG
					fout << "!! same case on " << lhEdge[i]->number << "!!" << endl;
					fout << lhAll[j]->number << "(" << lhAll[j]->vector.x << "," << lhAll[j]->vector.y << "," << lhAll[j]->isEdge << ") and "
						<< lhAll[longestShelterNum - 1]->number << "("
						<< lhAll[longestShelterNum - 1]->vector.x << "," << lhAll[longestShelterNum - 1]->vector.y << "," << lhAll[longestShelterNum - 1]->isEdge << ")" << endl;
#endif
					if (lhAll[j]->vector < lhAll[longestShelterNum - 1]->vector) {
						longestDist = dist;
						longestShelterNum = lhAll[j]->number;
#ifdef MY_DEBUG
						fout << "   selected " << longestShelterNum << endl;
#endif
					}
				}
			}
#ifdef MY_DEBUG
			if (lhAll[longestShelterNum - 1]->isEdge == false)
				fout << "   shelter is not edge : " << longestShelterNum << endl;
#endif
			lhEdge[i]->shelter = longestShelterNum;
		}

#ifdef MY_DEBUG
		for (int i = n; i >= 0; --i) {
			fout << setw(3) << i << "/";
			for (int j = 0; j <= n; ++j) {
				if (map[i][j] != -1)
					fout << setw(4) << map[i][j];
				else
					fout << setw(4) << " ";
			}
			fout << endl;
		}
		fout << "   /";
		for (int j = 0; j <= n; ++j) {
			fout << setw(3) << j << "/";
		}
		fout << "\n" << endl;

		for (int i = 0; i < lhEdge.size(); ++i) {
			fout << "<" << setw(3) << lhEdge[i]->number << "-" << setw(3) << lhEdge[i]->right << ">";
			fout << " st=" << setw(3) << lhEdge[i]->shelter << " / edge=" << lhEdge[i]->isEdge << endl;
		}
		fout << "\n" << endl;
#endif
		
		//input alert
		//init
		int lhPreNumA = 0, lhPreNumB = 0;
		int lhNumA = 0, lhNumB = 0;
		bool isSetFirst = false;

		int /*long long*/ result = 0;

		for (int i = 0; i < m; ++i) {
			fin >> lhNumA >> lhNumB;
#ifdef MY_DEBUG
			fout << "alert (" << setw(3) << lhNumA << "," << setw(3) << lhNumB << ")";
#endif
			lightHouseNumSort(&lhNumA, &lhNumB);

			if (isSetFirst == false) { 
				// init case, validation
				vector<LightHouse*>::iterator it;
				for (it = lhEdge.begin(); it != lhEdge.end(); ++it) {
					int candidateA = (*it)->number;
					int candidateB = (*it)->right;
					lightHouseNumSort(&candidateA, &candidateB);
					if (candidateA == lhNumA && candidateB == lhNumB) { //valid alert
						int targetNum = (lhAll[lhNumA - 1]->right == lhNumB) ? lhNumA : lhNumB;
						//***** add distance *****
						result += lhAll[targetNum - 1]->shelter;
#ifdef MY_DEBUG
						fout << "    add!   " << setw(3) << lhAll[targetNum - 1]->shelter << ", result=" << result << endl;
#endif

						lhPreNumA = lhNumA, lhPreNumB = lhNumB;
						isSetFirst = true;
						break;
					} // else case invalid alert
#ifdef MY_DEBUG
					fout << "    falut! by not init" << endl;
#endif
				}
			}
			else {
				//check validation 1 : each is edge
				if (lhAll[lhNumA - 1]->isEdge == false || lhAll[lhNumB - 1]->isEdge == false) {
#ifdef MY_DEBUG
					fout << "    falut! by is not edge" << endl;
#endif
					continue; //end case, is not edge
				}
				//check validation 2 : one of lighthouse must duplicate
				if (lhNumA == lhPreNumA && lhNumB == lhPreNumB) {
#ifdef MY_DEBUG
					fout << "    falut! by all duplicated" << endl;
#endif
					continue; //end case, all duplicated
				}
				int dupNum = -1, newNum = -1;
				if (lhPreNumA == lhNumA) dupNum = lhNumA, newNum = lhNumB;
				else if (lhPreNumA == lhNumB) dupNum = lhNumB, newNum = lhNumA;
				else if (lhPreNumB == lhNumA) dupNum = lhNumA, newNum = lhNumB;
				else if (lhPreNumB == lhNumB) dupNum = lhNumB, newNum = lhNumA;
				else {
#ifdef MY_DEBUG
					fout << "    falut! by not duplicated" << endl;
#endif
					continue; //end case, not duplicated
				}
				
				if (lhAll[dupNum - 1]->right != newNum && lhAll[dupNum - 1]->left != newNum) {
#ifdef MY_DEBUG
					fout << "    falut! by not neer location" << endl;
#endif
					continue; //end case, is not neer location
				}
				
				int targetNum = (lhAll[lhNumA - 1]->right == lhNumB) ? lhNumA : lhNumB;
				//***** add distance *****
				result += lhAll[targetNum - 1]->shelter;
#ifdef MY_DEBUG
				fout << "    add!   " << setw(3) << lhAll[targetNum - 1]->shelter << ", result=" << result << endl;
#endif
				lhPreNumA = lhNumA, lhPreNumB = lhNumB;
			}
		}

		fout << result % retDivNum << endl;

		//release
		vector<LightHouse*>::iterator releaseIt;
		for (releaseIt = lhAll.begin(); releaseIt != lhAll.end(); ++releaseIt) {
			LightHouse* temp = *releaseIt;
			delete temp;
		}
		delete lhMax;
	}

	fout.close();
	fin.close();
	return 0;
}

