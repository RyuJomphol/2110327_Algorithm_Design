#include <iostream>
#include <vector>

using namespace std;

int mod_num = 32717;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;

    vector<int> coefficients(k);
    for (int i = 0; i < k; i++) {
        cin >> coefficients[i];
    }

    int size = max(k, n) + 1;
    vector<int> recur(size);

    for (int i = 0; i < k; i++) {
        cin >> recur[i];
        recur[i] %= mod_num;
    }

    if (n < k) {
        cout << recur[n] << endl;
        return 0;
    }
    else {
        for (int i = k; i <= n; i++) {
            long long sum = 0;
            for (int j = 1; j <= k; j++) {
                long long temp = (long long)coefficients[j - 1] * recur[i - j];
                sum += temp % mod_num;
            }
            recur[i] = sum % mod_num;
        }
        cout << recur[n] << endl;
    }
}