#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 1) {
        cout << "3" << "\n";
        return 0;
    }

    int MOD = 100000007;
    int A = 1, B = 0, C = 1;

    for (int i = 2; i <= n; i++) {
        int nextA = (A + B + C) % MOD;
        int nextB = A % MOD;
        int nextC = (C + (2 * B) % MOD) % MOD;
        A = nextA;
        B = nextB;
        C = nextC;
    }

    int ans = (2 * A) % MOD;
    ans = (ans + (2 * B) % MOD) % MOD;
    ans = (ans + C) % MOD;

    cout << ans << "\n";
}