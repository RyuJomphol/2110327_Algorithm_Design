#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n + 1, vector<int>(m + 1));
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }
    
    dp[1][1] = grid[1][1];

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= m; c++) {
            if (r == 1 && c == 1) continue;

            int from_above = -1, from_left = -1, from_diagonal = -1;
            if (r > 1) from_above = dp[r - 1][c] + grid[r][c];
            if (c > 1) from_left = dp[r][c - 1] + grid[r][c];
            if (r > 1 && c > 1) from_diagonal = dp[r - 1][c - 1] + (2LL * grid[r][c]);
            dp[r][c] = max({from_above, from_left, from_diagonal});
        }
    }
    cout << dp[n][m] << "\n";
}