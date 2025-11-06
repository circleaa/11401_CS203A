#include<iostream>
using namespace std;

int main()
{
	int t, n;
	cin >> t;
	for (int Case = 1;Case <= t;Case++)
	{
		cin >> n;
		int min = 99, max = 0;
		for (int i = 1;i <= n;i++)
		{
			int x;
			cin >> x;
			if (x >= max) 
				max = x;
			if (x <= min) 
				min = x;
		}
		cout << (max - min) * 2 << endl;
	}
}