#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int INF = 1e9;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    vector<vector<int>> dp(N + 1, vector<int>(M + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 1; k * k <= j; k++) {
                int area_k = k * k;
                if (dp[i - 1][j - area_k] != INF) {
                    int cost = (A[i] - k) * (A[i] - k);
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - area_k] + cost);
                }
            }
        }
    }
    if (dp[N][M] == INF) {
        cout << -1 << endl;
    } else {
        cout << dp[N][M] << endl;
    }
}