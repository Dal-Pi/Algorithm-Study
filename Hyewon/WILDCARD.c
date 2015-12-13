#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int T;
int N;
int R;
char W[102];
char S[51][102];
char ANSWERS[51][102];
int CACHE[51][101][101];

int comparisonFuncitonString(const void * a, const void * b)
{
	return (strcmp((char *) a, (char *) b));
}

int check(int idx, int w, int s){

	if (CACHE[idx][w][s] != -1){
		return CACHE[idx][w][s];
	}

	while (W[w] != '\0' && S[idx][s] != '\0' && (W[w] == '?' || W[w] == S[idx][s])){
		if (check(idx, w + 1, s + 1) == 1){
			CACHE[idx][w][s] = 1;
			return 1;
		}
		else{
			CACHE[idx][w][s] = 0;
			return 0;
		}
	}


	if (W[w] == '\0'){
		if (S[idx][s] == '\0'){
			CACHE[idx][w][s] = 1;
			return 1;
		}
		else{
			CACHE[idx][w][s] = 0;
			return 0;
		}
	}
	
	if (W[w] == '*'){
		if (check(idx, w+1, s) == 1){
			CACHE[idx][w][s] = 1;
			return 1;
		}
		if (S[idx][s] != '\0' && check(idx, w, s + 1) == 1){
			CACHE[idx][w][s] = 1;
			return 1;
		}
	}

	CACHE[idx][w][s] = 0;
	return 0;
}

int main(){

	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	while (T--){
		R = 0;
		int i, j, k;
		for (i = 0; i < 51; i++){
			for (j = 0; j < 101; j++){
				for (k = 0; k < 101; k++){
					CACHE[i][j][k] = -1;
				}
			}
		}
		scanf("%s", &W);
		scanf("%d", &N);

		int n;
		for (n = 1; n <= N; n++){
			scanf("%s", &S[n]);
		}

		for (n = 1; n <= N; n++){
			if (check(n, 0, 0) == 1){
				strcpy(ANSWERS[R++], S[n]);
			}
		}

		qsort((void *) ANSWERS, R, sizeof(ANSWERS[0]), comparisonFuncitonString);
		
		for (n = 0; n < R; n++){
			printf("%s\n", ANSWERS[n]);
		}
	}

}