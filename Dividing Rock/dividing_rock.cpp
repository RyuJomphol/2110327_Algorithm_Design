#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (k > n || k == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    int MOD = 1997;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j == 1 || i == j) {
                dp[i][j] = 1;
            } else if (i > j) {
                dp[i][j] = (dp[i - 1][j - 1] + (j * dp[i - 1][j]) % MOD) % MOD;
            } else {
                dp[i][j] = 0;
            }
        }
    }
    cout << dp[n][k] << endl;
}