#include <iostream>
using namespace std;

int oddSum(int a, int b)
{
	if (a < b)
		return a + oddSum(a + 2, b);

	else
		return 0;
}

int main()
{
	int T, a, b;
	cin >> T;
	for (int i = 1; i <= T; i++)
	{
		cin >> a >> b;
		if (a % 2 == 0)
			a++;
		if (b % 2 == 1)
			b++;

		cout << "Case " << i << ": " << oddSum(a, b) << endl;
	}
}