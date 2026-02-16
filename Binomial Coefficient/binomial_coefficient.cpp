#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            } else {
                // C(n, k) = C(n-1, k-1) + C(n-1, k)
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }
    cout << dp[n][k] << endl;
}
