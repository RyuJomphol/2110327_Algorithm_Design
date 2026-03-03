#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int INF = 1e9;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> p(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> p[i];
    }

    vector<int> dp(N + 1, INF);
    deque<int> dq;

    for (int i = 1; i <= N; i++) {
        if (i <= K + 1) {
            dp[i] = p[i];
        } else {
            while (!dq.empty() && dq.front() < i - 2 * K - 1) {
                dq.pop_front();
            }

            if (!dq.empty()) {
                dp[i] = dp[dq.front()] + p[i];
            }
        }

        while (!dq.empty() && dp[dq.back()] >= dp[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    int min_cost = INF;
    for (int i = max(1, N - K); i <= N; i++) {
        min_cost = min(min_cost, dp[i]);
    }
    cout << min_cost << endl;
}