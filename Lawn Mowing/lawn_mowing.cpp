#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> p(n + 1, 0);
    for  (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        p[i + 1] = p[i] + val;
    }

    while(m--) {
        int l, budget;
        cin >> l >> budget;

        int low = l, high = n - 1;
        int best_r = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int grass_sum = p[mid + 1] - p[l];
            int total_cost = grass_sum + (mid - l + 1) * k;

            if (total_cost <= budget) {
                best_r = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        if (best_r == -1) {
            cout << "0\n";
        }
        else {
            cout << p[best_r + 1] - p[l] << "\n";
        }
        
    }
}