#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool dp[101][100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> A(n);
    int max_sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
        max_sum += A[i];
    }

    dp[0][0] = true;
    for(int i = 0; i < n; i++) {
        int num = A[i];
        for (int j = m; j >= 1; j--) {
            for (int s = max_sum; s >= num; s--) {
                if (dp[j - 1][s - num] == true) {
                    dp[j][s] = dp[j][s] | dp[j - 1][s - num];
                }
            }
        }
    }

    int min_diff = 2e9;
    for(int s = 0; s <= max_sum; s++) {
        if (dp[m][s]) {
            int current_diff = abs(s - k);
            if (current_diff < min_diff) {
                min_diff = current_diff;
            }
        }
    }

    cout << min_diff << endl;
}