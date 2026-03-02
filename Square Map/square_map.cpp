#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    cin >> R >> C;

    vector<vector<int>> dp(R + 1, vector<int>(C + 1, 0));
    int max_k = 0;

    for (int i = 1; i <= R; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= C; j++) {
            if (row[j - 1] == '1') {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                if (dp[i][j] > max_k) {
                    max_k = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    cout << max_k << endl;
}