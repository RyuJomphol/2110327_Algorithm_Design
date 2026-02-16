#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n + 1);

    dp[0] = 0; // F(0) = 0
    if (n > 0) {
        dp[1] = 1; // F(1) = 1
    }

    for (int i = 2; i <= n; i++) {
        // F(n) = F(n-1) + F(n-2)
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n] << endl;
}