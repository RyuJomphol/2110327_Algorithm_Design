#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long sum[200005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;

    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        sum[i] = sum[i - 1] + (d - m);
    }

    for (int i = 0; i < k; i++) {
        int p;
        long long w;
        cin >> p >> w;

        long long target = w + sum[p - 1];
        auto it = lower_bound(sum + p, sum + n + 1, target);
        cout << (it - sum) << endl;
    }
}