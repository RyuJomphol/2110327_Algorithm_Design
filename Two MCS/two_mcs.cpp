#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    if (n == 0) return 0;

    vector<ll> L(n);
    ll current_max = -2e18;
    ll best_so_far = -2e18;
    ll running_sum = 0;

    for (int i = 0; i < n; i++) {
        running_sum += A[i];
        if (running_sum > best_so_far) {
            best_so_far = running_sum;
        }
        L[i] = best_so_far;
        if (running_sum < 0) {
            running_sum = 0;
        }
    }

    vector<ll> R(n);
    best_so_far = -2e18;
    running_sum = 0;

    for (int i = n - 1; i >= 0; i--) {
        running_sum += A[i];
        if (running_sum > best_so_far) {
            best_so_far = running_sum;
        }
        R[i] = best_so_far;
        if (running_sum < 0) {
            running_sum = 0;
        }
    }

    ll ans = -2e18;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, L[i] + R[i + 1]);
    }

    ans = max(ans, L[n - 1]); // In case we take the whole array as one segment

    cout << ans << "\n";
}