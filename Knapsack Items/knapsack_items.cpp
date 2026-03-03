#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> weights(n + 1);
    vector<int> values(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> values[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> weights[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> dp[i][j];
        }
    }

    vector<int> selected_items;
    int current_weight = m;
    for (int i = n; i >= 1; i--) {
        if (dp[i][current_weight] != dp[i - 1][current_weight]) {
            selected_items.push_back(i);
            current_weight -= weights[i];
        }
    }

    cout << selected_items.size() << endl;
    for (int i = 0; i < selected_items.size(); i++) {
        cout << selected_items[i] << (i == selected_items.size() - 1 ? "" : " ");
    }
    cout << endl;
}