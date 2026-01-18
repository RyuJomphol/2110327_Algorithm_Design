#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long x;
    cin >> x;

    if (x == 0) {
        cout << 0 << endl;
        return 0;
    }

    int min_ops = 24;
    const int MOD_VAL = 16777216;

    for (int j = 0; j <= 24; j++) {
        int divisor = 1 << (24 - j); 
        int remainder = x % divisor;
        int i = (remainder == 0) ? 0 : (divisor - remainder);
        min_ops = min(min_ops, i + j);
    }

    cout << min_ops << endl;
    return 0;
}