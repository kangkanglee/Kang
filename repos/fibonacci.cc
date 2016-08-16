#include <iostream>

using namespace std;

int main()
{
    int f_pos = 0;
    int s_pos = 1;
    int result = 1;
    int n = 10;
    while(n > 2) {
        --n;
        f_pos = s_pos;
        s_pos = result;
        result = f_pos + s_pos;
        cout << result << endl;
    }
}
