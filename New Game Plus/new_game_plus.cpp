#include <iostream>
#include <vector>

using namespace std;

int MOD = 100000007;

int R, C;
int grid[505][505];
long long dp[505][505][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
        }
    }

    for (int r = 1; r <= R; r++) {
        if (grid[r][1] == 1) continue;

        if (r - 1 >= 1 && grid[r - 1][2] == 0) {
            dp[r - 1][2][0] = (dp[r -1][2][0] + 1) % MOD;
        }

        if (grid[r][2] == 0) {
            dp[r][2][1] = (dp[r][2][1] + 1) % MOD;
        }

        if (r + 1 <= R && grid[r + 1][2] == 0) {
            dp[r + 1][2][2] = (dp[r + 1][2][2] + 1) % MOD;
        }
    }

    for (int c = 2; c < C; c++) {
        for (int r = 1; r <= R; r++) {
            if (grid[r][c] == 1) continue;

            if (r - 1 >= 1 && grid[r - 1][c + 1] == 0) {
                dp[r - 1][c + 1][0] = (dp[r - 1][c + 1][0] + dp[r][c][1] + dp[r][c][2]) % MOD;
            }
            if (grid[r][c + 1] == 0) {
                dp[r][c + 1][1] = (dp[r][c + 1][1] + dp[r][c][0] + dp[r][c][2]) % MOD;
            }
            if (r + 1 <= R && grid[r + 1][c + 1] == 0) {
                dp[r + 1][c + 1][2] = (dp[r + 1][c + 1][2] + dp[r][c][0] + dp[r][c][1]) % MOD;
            }
        }
    }

    long long total_ways = 0;
    if (C == 1) {
        for (int r = 1; r <= R; r++) {
            if (grid[r][1] == 0) {
                total_ways = (total_ways + 1) % MOD;
            }
        }
    } else {
        for (int r = 1; r <= R; r++) {
            if (grid[r][C] == 0) {
                total_ways = (total_ways + dp[r][C][0] + dp[r][C][1] + dp[r][C][2]) % MOD;
            }
        }
    }

    cout << total_ways << endl;
}