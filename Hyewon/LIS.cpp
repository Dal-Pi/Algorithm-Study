#include <stdio.h>
int T;
int N;
int ARR[501];
int CACHE[501];
int RESULT;

int max(int a, int b){
	return a > b ? a : b;
}

int lis(){
	int idx = 0, i, j;

	CACHE[idx++] = ARR[0];

	for (i = 1; i < N; i++){
		if (CACHE[idx - 1] < ARR[i]){
			CACHE[idx++] = ARR[i];
		}
		else{
			for (j = 0; j < i; j++){
				if (CACHE[j] > ARR[i]){
					CACHE[j] = ARR[i];
					break;
				}
			}
		}
	}

	return idx;

}

int lis_cur(int idx){
	int& ret = CACHE[idx];

	if (ret != -1){
		return ret;
	}
	ret = 1;

	int i;
	for (i = idx + 1; i < N; i++){
		if (ARR[idx] < ARR[i]){

			ret = max(ret, lis_cur(i) + 1);
		}
	}
	return ret;
}

int main(){

	freopen("sample_input.txt", "r", stdin);

	scanf("%d", &T);

	while (T--){
		scanf("%d", &N);
		int i, n;

		RESULT = -1;

		for (n = 0; n < N; n++){
			scanf("%d", &ARR[n]);
		}

		/* 
		// recursive
		for (n = 0; n < N; n++){
			for (i = 0; i < N; i++){
				CACHE[i] = -1;
			}
			RESULT = max(RESULT, lis_cur(n));
		}

		*/

		for (i = 0; i < N; i++){
			CACHE[i] = -1;
		}
		RESULT = lis();

		printf("%d\n", RESULT);

	}
}