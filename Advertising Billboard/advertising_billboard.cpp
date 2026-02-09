#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> ads(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> ads[i];
    }

    if (N == 0) {
        cout << 0 << "\n";
        return 0;
    }
    if (N == 1) {
        cout << ads[1] << "\n";
        return 0;
    }

    vector<int> dp(N + 1);
    dp[0] = 0;
    dp[1] = ads[1];

    for (int i = 2; i <= N; i++) {
        int skip_current = dp[i - 1];
        int take_current = dp[i - 2] + ads[i];
        dp[i] = max(skip_current, take_current);
    }

    cout << dp[N] << "\n";
    return 0;
}