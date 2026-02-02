#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, w;
    cin >> n >> w;
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        p[i] = p[i - 1] + val;
    }

    deque<int> dq;
    dq.push_back(0);

    int max_sum = -2e8;

    for (int j = 1; j <= n ; j++) {
        if(!dq.empty() && dq.front() < j - w) {
            dq.pop_front();
        }

        if (!dq.empty()) {
            max_sum = max(max_sum, p[j] - p[dq.front()]);
        }

        while(!dq.empty() && p[dq.back()] >= p[j]) {
            dq.pop_back();
        }
        dq.push_back(j);
    }

    cout << max_sum << endl;
}