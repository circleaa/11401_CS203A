#include<iostream>
using namespace std;

int main()
{
	int a, b, c, d, L;
	while (cin >> a >> b >> c >> d >> L)
	{
		if (a == 0 && b == 0 && c == 0 && d == 0 && L == 0)
			break;
		int n = 0;
		for (int x = 0;x <= L;x++)
		{
			if ((a * x * x + b * x + c) % d == 0)
				++n;
		}
		cout << n << endl;
	}
}
