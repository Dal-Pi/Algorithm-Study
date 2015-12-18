
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

char W[101];
int n = 0;
char S[50][101];
int wSize, sSize;
int myCache[101][101] = { -1, };
char *answers[51];
int answerCount = 0;

bool match(int w, int s, int sIndex);

int main() {
	int testCase = 0;

	scanf("%d", &testCase);

	for (int C = 0; C < testCase; ++C) {
		answerCount = 0;

		scanf("%s", W);
		wSize = strlen(W);
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 101; ++j)
				for (int k = 0; k < 101; ++k)
					myCache[j][k] = -1;
			scanf("%s", S[i]);
			sSize = strlen(S[i]);
			if (match(0, 0, i))
				answers[answerCount++] = S[i];
		}
		for (int i = 0; i < answerCount; ++i) {
			for (int j = i; j < answerCount; ++j) {
				if (strcmp(answers[i], answers[j]) > 0) {
					char temp[101];
					strcpy(temp, answers[i]);
					strcpy(answers[i], answers[j]);
					strcpy(answers[j], temp);
				}
			}
		}
		for (int i = 0; i < answerCount; ++i)
			printf("%s\n", answers[i]);
	}
	return 0;
}

bool match(int w, int s, int sIndex) {
	int result = false;

	if (w == wSize)
		return (s == sSize);

	if (myCache[w][s] != -1)
		return myCache[w][s];

	if (W[w] == '*') {
		result |= (myCache[w+1][s] = match(w + 1, s, sIndex));
		result |= (myCache[w][s+1] = (s < sSize && match(w, s + 1, sIndex)));
	}
	else if (W[w] == '?' || W[w] == S[sIndex][s]) {
		result |= (myCache[w+1][s+1] = match(w + 1, s + 1, sIndex));
	}
	myCache[w][s] = result;
	return result;
}
