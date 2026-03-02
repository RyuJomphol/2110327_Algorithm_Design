#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 5005;
int A[MAXN];
int memo[MAXN][MAXN];
int n;

int solve(int L, int R) {
    if (L >= R) return 0;
    if (memo[L][R] != -1) return memo[L][R];

    int pickLeftLeft = max(A[L], A[L + 1]) + solve(L + 2, R);
    int pickRightRight = max(A[R], A[R - 1]) + solve(L, R - 2);
    int pickLeftRight = max(A[L], A[R]) + solve(L + 1, R - 1);
    return memo[L][R] = max({pickLeftLeft, pickRightRight, pickLeftRight});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    memset(memo, -1, sizeof(memo));

    cout << solve(0, n - 1) << "\n";
}