#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll P, K, A, B;
vector<ll> pos;

ll count_avengers(ll L, ll R) {
    auto it1 = lower_bound(pos.begin(), pos.end(), L);
    auto it2 = upper_bound(pos.begin(), pos.end(), R);
    return distance(it1, it2);
}

ll destroy_base(ll L, ll R) {
    ll m = count_avengers(L, R);
    ll cost_destroy;

    if (m == 0) {
        cost_destroy = A;
    }
    else {
        cost_destroy = B * m * (R - L + 1);
    }

    if (L == R || m == 0) {
        return cost_destroy;
    }

    ll mid = L + (R - L) / 2;

    return min(cost_destroy, destroy_base(L, mid) + destroy_base(mid + 1, R));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> P >> K >> A >> B;

    pos.resize(K);
    for (int i = 0; i < K; i++) {
        cin >> pos[i];
    }
    sort(pos.begin(), pos.end());

    ll n = 1LL << P;
    cout << destroy_base(1, n) << endl;

    return 0;
}