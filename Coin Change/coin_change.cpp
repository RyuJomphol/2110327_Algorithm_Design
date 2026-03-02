#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    vector<int> coins(N);
    for (int i = 0; i < N; i++) {
        cin >> coins[i];
    }
    vector<int> dp(M + 1, M + 1);
    dp[0] = 0;

    for (int coin : coins) {
        for (int j = coin; j <= M; j++) {
            if (dp[j - coin] + 1 < dp[j]) {
                dp[j] = dp[j - coin] + 1;
            }
        }
    }
    cout << dp[M] << endl;
}