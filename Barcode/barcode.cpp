#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<long long>> dp(N + 1, vector<long long>(K + 1, 0));

    for (int i = 1; i <= N; i++) {
        if (i <= M) {
            dp[i][0] = 1;
        } else {
            dp[i][0] = 0;
        }
    }

    for (int j = 1; j <= K; j++) {
        for (int i = 1; i <= N; i++) {
            for (int len = 1; len <= M; len++) {
                if (i - len >= 1) {
                    dp[i][j] += dp[i - len][j - 1];
                }
            }
        }
    }

    cout << dp[N][K] << endl;
}