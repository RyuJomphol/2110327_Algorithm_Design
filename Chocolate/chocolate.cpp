#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> s_set(k);
    for (int i = 0; i < k; i++) {
        cin >> s_set[i];
    }

    int MOD = 1000003;
    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            int step = s_set[j];
            if (i >= step) {
                dp[i] = (dp[i] + dp[i - step]) % MOD;
            }
        }
    }
    cout << dp[n] << endl;
}