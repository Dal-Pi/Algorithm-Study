#include <stdio.h>

int triangle[101][101];
int cached[101][101];
int n = 0;

int max(int a, int b);
int getSum(int y, int x);

int main() {

	int testcase;
	scanf("%d", &testcase);

	for (int C = 0; C < testcase; ++C) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				scanf("%d", &triangle[i][j]);
			}
		}
		//init cache
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cached[i][j] = -1;
			}
		}

		printf("%d\n", getSum(0, 0));
	}
	return 0;
}

int getSum(int y, int x) {
	if (y == n - 1)
		return triangle[y][x];

	if (cached[y][x] != -1)
		return cached[y][x];
	else
		return cached[y][x] = triangle[y][x] + max(getSum(y + 1, x), getSum(y + 1, x + 1));
}

int max(int a, int b) {
	return (a > b) ? a : b;
}