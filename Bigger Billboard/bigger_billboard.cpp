#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    vector<long long> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        long long option1 = dp[i - 1];
        long long option2 = c[i];
        if (i >= 3) {
            option2 += dp[i - 3];
        }
        dp[i] = max(option1, option2);
    }
    cout << dp[n] << endl;
}