#include <stdio.h>
int T;
int N;
int TRI[101][101];
int CACHE[101][101];

int max(int a, int b){
	return a > b ? a : b;
}
int check_dp(int r, int c){
	int& ret = CACHE[r][c];
	if (ret != -1){
		return ret;
	}
	if (r == N - 1){
		return TRI[r][c];
	}
	return ret = max(check_dp(r + 1, c), check_dp(r + 1, c + 1)) + TRI[r][c];
}

int check_rec(int r, int c, int v){
	v = v + TRI[r][c];
	if (r == N - 1){
		return v;
	}
	return max(check_rec(r + 1, c, v), check_rec(r + 1, c + 1, v));
}

int main(){

	freopen("sample_input.txt", "r", stdin);

	scanf("%d", &T);
	while (T--){
		scanf("%d", &N);
		int r, c;
		for (r = 0; r < N; r++){
			for (c = 0; c <= r; c++){
				scanf("%d", &TRI[r][c]);
				CACHE[r][c] = -1;
			}
		}

		//int result = check_rec(0, 0, 0);
		int result = check_dp(0, 0);
		printf("%d\n", result);

	}
	
}