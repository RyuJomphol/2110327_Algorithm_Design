#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int max_degree = 0;
    int n;
    cin >> n;

    vector<vector<int>> degree(n, vector<int>(n, 0));
    vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> degree[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        int degree_sum = 0;
        for (int j = 0; j < n; ++j) {
            degree_sum += degree[i][j];
        }
        ans[i] = degree_sum;
        if (degree_sum > max_degree) {
            max_degree = degree_sum;
        }
    }

    vector<int> count_freq(max_degree + 1, 0);
    for (int i = 0; i < n; ++i) {
        count_freq[ans[i]]++;
    }

    for (int i = 0; i <= max_degree; i++) {
        cout << count_freq[i] << " ";
    }
    cout << endl;

    return 0;
}