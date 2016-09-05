#include <iostream>
#include <vector>
using namespace std;

int square_cost(int n)
{
	vector<int> c(n + 1, 0);
	c[0] = 0;
	for (int i = 1; i <= n; ++i) {
		int t = sqrt(i);
		if (i - t * t == 0)
			c[i] = 1;
		else {
			int min_cost= INT_MAX;
			for (int j = 1; j < i; ++j) {
				int temp_cost = c[j] + c[i - j];
				if (temp_cost < min_cost)
					min_cost = temp_cost;
			}
			c[i] = min_cost;
		}
	}
	return c[n];
}

int main()
{
	int n = 0;
	while (cin >> n) {
		cout << square_cost(n) << endl;
	}
	//cout << NumOfSquare(100) << endl;
	system("pause");
	return 0;
}