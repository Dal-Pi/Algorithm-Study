#include <stdio.h>

int T;
int N;
int MAP[101][101];
int MEMO[101][101];

int go(int r, int c){

	if (r >= N || c>=N){
		return 0;
	}

	if (r == N - 1 && c == N - 1){
		return 1;
	}

	if (MEMO[r][c] != -1){
		return MEMO[r][c];
	}

	int size = MAP[r][c];
	
	if (go(r + size, c) == 1 || go(r, c+size) == 1){
		MEMO[r][c] = 1;
		return 1;
	}
	else{
		MEMO[r][c] = 0;
		return 0;
	}
}

int main(){
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	while (T--){

		scanf("%d", &N);
		int r,c;
		for (r = 0; r < N; r++){
			for (c = 0; c < N; c++){
				scanf("%d", &MAP[r][c]);
				MEMO[r][c] = -1;
			}
		}

		if (go(0, 0) == 1){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
}