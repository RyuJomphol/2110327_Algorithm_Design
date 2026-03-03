#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    vector<int> dp(N, 1);
    int max_length = 1;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (S[i] > S[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_length = max(max_length, dp[i]);
    }

    cout << max_length << endl;
}