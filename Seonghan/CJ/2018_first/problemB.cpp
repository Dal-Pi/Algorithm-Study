#if 0

#include <iostream>
using namespace std;

int main()
{
	int N = 0, K = 0, M = 0;
	cin >> N >> K >> M;

	int pos = K;

	int input = -1;
	for (int i = 0; i < N; ++i)
		cin >> input; //not use

	for (int i = 0; i < M; ++i)
	{
		cin >> input;
		if (input > 0)
		{
			if (input >= pos)
			{
				pos = input - pos + 1;
			}
		}
		else
		{
			int rtol = N + input + 1;
			if (pos >= rtol)
			{
				pos = N - (pos - rtol);
			}
		}

		//debug
		//cout << i << " times, pos = " << pos << endl;
	}

	cout << pos << endl;
}


#endif
