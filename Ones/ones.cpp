#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

map<pair<int,int>, int> memo;
int q[15];

int solve(int n, int k) {
    if (k == 1) return n;

    if (memo.count({n, k})) return memo[{n, k}];

    int cnt = n / q[k];
    int rem = n % q[k];
    int res = cnt * k + solve(rem, k - 1);

    res = min(res, (cnt + 1) * k + solve(q[k] - rem, k - 1));

    return memo[{n, k}] = res;
}

int main() {
    int n;
    cin >> n;

    q[1] = 1;
    for (int i = 2; i <= 12 ; i++) {
        q[i] = q[i - 1] * 10 + 1;
    }

    int start_k = 1;
    while (start_k < 12 && q[start_k] < n) {
        start_k++;
    }

    cout << solve(n, start_k) << endl;
}