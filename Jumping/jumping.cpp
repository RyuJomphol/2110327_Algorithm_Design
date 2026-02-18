#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    vector<int> dp(n + 1);

    dp[1] = arr[1];
    if (n >= 2) {
        dp[2] = arr[1] + arr[2];
    }

    if (n >= 3) {
        dp[3] = max(dp[1], dp[2]) + arr[3];
    }

    for (int i = 4; i <= n; i++) {
        dp[i] = max({dp[i - 1], dp[i - 2], dp[i - 3]}) + arr[i];
    }

    cout << dp[n] << "\n";
}