#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int MOD = 100000007;

    int a = 1, b = 1;

    for (int i = 2; i <= n; i++) {
        int next_a = (a + 2 * b) % MOD;
        int next_b = (a + b) % MOD;
        a = next_a;
        b = next_b;
    }

    int ans = (a + 2 * b) % MOD;
    cout << ans << "\n";
}