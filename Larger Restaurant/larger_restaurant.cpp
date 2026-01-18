#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    int N, A;
    if (!(cin >> N >> A)) return 0;

    vector<ll> T(N);
    for (int i = 0; i < N; i++) {
        cin >> T[i];
    }

    vector<ll> customers(A);
    for (int i = 0; i < A; i++) {
        cin >> customers[i];
    }

    for (int k = 0; k < A; k++) {
        ll target_customer = customers[k];
        
        ll low = 0, high = 2e14; 
        ll ans = high;

        while (low <= high) {
            ll mid = low + (high - low) / 2;
            
            ll total_seated = 0;
            for (int i = 0; i < N; i++) {
                total_seated += (mid / T[i]) + 1;
            }

            if (total_seated >= target_customer) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        cout << ans << "\n";
    }

    return 0;
}