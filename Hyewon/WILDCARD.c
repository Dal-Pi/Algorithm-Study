#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int T;
int N;
int R;
char W[102];
char S[51][102];
char ANSWERS[51][102];

int comparisonFuncitonString(const void * a, const void * b)
{
	return (strcmp((char *) a, (char *) b));
}

int check(int idx, int w, int s){

	while (W[w] != '\0' && S[idx][s] != '\0' && (W[w] == '?' || W[w] == S[idx][s])){
		++w;
		++s;
	}

	if (W[w] == '\0'){
		if (S[idx][s] == '\0'){
			return 1;
		}
		else{
			return 0;
		}
	}
	
	if (W[w] == '*'){
		int skip = 0;
		while (1){
			if (check(idx, w + 1, s + skip) == 1){
				return 1;
			}
			if (S[idx][s + skip] == '\0'){
				break;
			}
			else{
				skip++;
			}
		}
	}

	return 0;
}

int main(){

	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	while (T--){
		R = 0;
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