#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int mod_num = 100000007;

    vector<int> dp(n + 1);

    dp[0] = 1;

    for (int i = 1 ; i <= n; i++) {
        
        dp[i] = dp[i - 1];
        if (i < k) {
            dp[i] = (dp[i] + 1) % mod_num;
        }
        else {
            dp[i] = (dp[i] + dp[i - k]) % mod_num;
        }
    }
    cout << dp[n] << "\n";
}