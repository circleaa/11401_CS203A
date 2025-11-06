#include <iostream>
using namespace std;

int main()
{
	int T;
	cin >> T;
	
	for (int Case = 1;Case <= T;Case++)
	{
		int a, b;
		cin >> a >> b;
		if (a % 2 == 0)
			a++;

		int sum = 0;
		for (int i = a;i <= b;i = i + 2)
			sum += i;

		cout << "Case " << Case << ": " << sum << endl;
	}
	return 0;
}