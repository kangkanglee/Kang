// give a, b
// output aa, ab, ba, bb
#include <iostream>
#include <string>

using namespace std;

void get_all_array(string s, string r, int n)
{
	if (n == 0) {
		cout << r;
		cout << endl;
		return;
	}
	--n;
	string s_raw = r;
	for (int i = 0; i < s.size(); ++i) {
		r = s_raw + s[i];
		get_all_array(s, r, n);
	}
}

int main()
{
	string s;
	cin >> s;
	int n = s.size();
	string r;
	get_all_array(s, r, n);
	return 0;
}
