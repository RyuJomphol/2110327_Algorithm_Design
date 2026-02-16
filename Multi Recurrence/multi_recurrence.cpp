#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> R(n + 1);
    int mod_num = 32717;

    for (int i = 1; i <= k; i++) {
        cin >> R[i];
        R[i] %= mod_num;
    }

    for (int i = k + 1; i <= n; i++) {
        int p;
        cin >> p;

        int sum = 0;
        for (int j = 0; j < p; j++) {
            int b;
            cin >> b;

            int previous_index = i - b;
            if (previous_index > 0) {
                sum += R[previous_index];
                sum %= mod_num;
            }
        }
        R[i] = sum;
    }

    for (int i = 1; i <= n; i++) {
        cout << R[i] << " ";
    }
}