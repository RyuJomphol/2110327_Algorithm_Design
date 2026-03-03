#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string x, y;
    cin >> x >> y;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> dp[i][j];
        }
    }

    string lcs = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            lcs = x[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i][j] == dp[i - 1][j]) {
            i--;
        } else {
            j--;
        }
    }
    cout << lcs << endl;
}