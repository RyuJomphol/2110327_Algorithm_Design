#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<long long> b(k + 1);
    for (int p = 1; p <= k; p++) {
        cin >> b[p];
    }

    vector<long long> dp(n + 1, -INF);
    
    // Base Case
    dp[1] = a[1];

    for (int i = 2; i <= n; i++) {
        long long max_score = -INF;
        for (int p = 1; p <= k; p++) {
            if (i - p >= 1) {
                max_score = max(max_score, dp[i - p] - b[p]);
            }
        }
        dp[i] = max_score + a[i];
    }

    cout << dp[n] << endl;
}