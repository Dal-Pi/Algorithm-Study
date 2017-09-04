#include <stdio.h>

int num[502];
int cached[502];
int n;

int max(int a, int b);
int lis(int start);

int main() {

	int testcase;
	scanf("%d", &testcase);

	for (int C = 0; C < testcase; ++C) {
		scanf("%d", &n);

		num[0] = -1; //for start
		for (int i = 0; i < n; ++i)
			scanf("%d", &num[i + 1]);

		//init
		for (int i = 0; i < 502; ++i)
			cached[i] = -1;

		printf("%d\n", lis(0)); // -1?
	}
	return 0;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int lis(int start) {
	int ret = 0;
	//end case
	if (start == n)
		return 0;

	//if cached
	if (cached[start] != -1)
		return cached[start];

	for (int i = start + 1; i <= n; ++i) {
		if (num[i] > num[start]) {
			ret = max(ret, 1 + lis(i));
		}
	}

	return cached[start] = ret;
}