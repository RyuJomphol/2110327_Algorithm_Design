#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
int C[60];
int P[60];
int trans[60][2];
long long dp[60][60][2];

void precompute_transitions() {
    for (int j = 0; j < K; j++) {
        for (int bit = 0; bit < 2; bit++) {
            vector<int> current_seq;
            for (int m = 0; m < j; m++) current_seq.push_back(P[m]);
            current_seq.push_back(bit);

            for (int len = min((int)current_seq.size(), K); len >= 0; len--) {
                bool match = true;
                for (int m = 0; m < len; m++) {
                    if (current_seq[current_seq.size() - len + m] != P[m]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    trans[j][bit] = len;
                    break;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> C[i];
    }
    for (int i = 0; i < K; i++) {
        cin >> P[i];
    }
    
    precompute_transitions();

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < K; j++) {
            for (int bit = 0; bit < 2; bit++) {
                dp[i][j][bit] = -1;
            }
        }
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            for (int bit = 0; bit < 2; bit++) {
                if (dp[i][j][bit] == -1) continue;

                int nj0 = trans[j][0];
                if (nj0 < K) {
                    dp[i + 1][nj0][0] = max(dp[i + 1][nj0][0], dp[i][j][bit]);
                }

                if (bit == 0) {
                    int nj1 = trans[j][1];
                    if (nj1 < K) {
                        dp[i + 1][nj1][1] = max(dp[i + 1][nj1][1], dp[i][j][bit] + C[i + 1]);
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (int j = 0; j < K; j++) {
        ans = max(ans, max(dp[N][j][0], dp[N][j][1]));
    }
    cout << ans << "\n";
}