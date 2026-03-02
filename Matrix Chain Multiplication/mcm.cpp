#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long solve() {
    int N;
    cin >> N;

    vector<int> S(N + 1);
    for (int i = 0; i <= N; i++) {
        cin >> S[i];
    }

    vector<vector<long long>> dp(N + 1, vector<long long>(N + 1, 0));

    for (int L = 2; L <= N; L++) {
        for (int i = 1; i <= N - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {
                long long cost = dp[i][k] + dp[k + 1][j] + (long long)S[i - 1] * S[k] * S[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[1][N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << solve() << "\n";

    return 0;
}