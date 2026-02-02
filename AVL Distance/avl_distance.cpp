#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<vector<int>> adj;
int ans = 0;

vector<int> dfs(int u) {
    vector<int> current_dp(k + 1, 0);
    current_dp[0] = 1;

    for(int v : adj[u]) {
        vector<int> child_dp = dfs(v);

        for (int i = 0; i < current_dp.size(); i++) {
            int dist_from_u = i;
            int needed_dist_from_v = k - dist_from_u - 1;

            if (needed_dist_from_v >= 0 && needed_dist_from_v < child_dp.size()) {
                ans += current_dp[dist_from_u] * child_dp[needed_dist_from_v];
            }
        }

        for (int j = 0 ; j < child_dp.size() ; j++) {
            if (j + 1 <= k) {
                current_dp[j + 1] += child_dp[j];
            }
        }
    }

    return current_dp;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    adj.resize(n + 1);
    for (int i = 0 ; i < n - 1 ; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    dfs(1);

    cout << ans << endl;
}