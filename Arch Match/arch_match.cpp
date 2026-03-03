#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long A[505];
long long dp[505][505];

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);

            for (int k = i + 1; k <= j; k++) {
                long long score = A[i] * A[k];
                dp[i][j] = max(dp[i][j], score + dp[i + 1][k - 1] + dp[k + 1][j]);
            }
        }
    }

    cout << dp[1][n] << endl;
}