#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int INF = 1e9;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> min_p_minus_1(2005,INF);

    int current_prefix_sum = 0;
    int max_double_end_sum = -INF;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int idx = a + 1000;

        int potential_p_minus_1 = current_prefix_sum;

        if (potential_p_minus_1 < min_p_minus_1[idx]) {
            min_p_minus_1[idx] = potential_p_minus_1;
        }

        current_prefix_sum += a;

        int current_sum = current_prefix_sum - min_p_minus_1[idx];

        if (current_sum > max_double_end_sum) {
            max_double_end_sum = current_sum;
        }
    }
    cout << max_double_end_sum << endl;
}