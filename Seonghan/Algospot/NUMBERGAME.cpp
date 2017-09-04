#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int memorized[100000] = { -1, };

int max(int a, int b) {
	return (a > b) ? a : b;
}

int getDivider(int num) {
	int ret = 1;
	while ((ret * 10) <= num) {
		ret *= 10;
	}
	return ret;
}

void getCandidates(int mul, int num, int candidates[], int * candiCount) {
	int div = getDivider(num);
	for (int i = div; i >= 10; i /= 10) {
		candidates[(*candiCount)] = mul * (num / i) * (num % i);
		//debug
		//printf("candidate %d - %d * %d * %d\n", candidates[(*candiCount)], mul, (num / i), (num%i));
		(*candiCount) += 1;
		getCandidates(mul * (num / i), num % i, candidates, candiCount);
	}
}

int getMaxDepth(int num) {
	int candidates[16];
	int candiCount;
	int ret = 0;
	//endcase
	if (num < 10) {
		return 0;
	}
	//memo check
	if (memorized[num] > 0)
		return memorized[num];

	//else case
	candiCount = 0;
	getCandidates(1, num, candidates, &candiCount);
	for (int i = 0; i < candiCount; ++i) {
		ret = max(ret, getMaxDepth(candidates[i]) + 1);
	}
	//memorized[num] = ret;
	return ret;
}

int main() {
	int number = 0;

	scanf("%d", &number);

	printf("%d\n", getMaxDepth(number));

	return 0;
}