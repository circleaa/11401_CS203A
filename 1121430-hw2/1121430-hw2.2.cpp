#include<iostream>
using namespace std;

int main()
{
	int n,i,j;
	while (cin >> n)
	{
		if (n == 0)
			break;
		if(n >= 2000000000)
			return 0;

		while (n >= 10)
		{
			int sum = 0;
			i = 1000000000;
			while (n > 0)
			{
				j = n / i;
				n -= j * i;
				sum += j;
				i /= 10;
			}
			n = sum;
		}

		cout << n << endl;
	}
	return 0;
}
	

