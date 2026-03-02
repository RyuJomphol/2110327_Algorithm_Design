#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 200005;
int l[MAXN], r[MAXN];
ll pref_L[MAXN], pref_R[MAXN];
ll curr_L[MAXN], curr_R[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w, k;
    cin >> n >> w >> k;

    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }

    ll max_total = 0;

    for (int i = 1; i <= n; i++) {
        pref_L[i] = 0;
        pref_R[i] = 0;
    }

    for (int j = 1; j <= k; j++) {
        bool updated = false;
        for (int i = 1; i <= n; i++) {
            curr_L[i] = -1;
            curr_R[i] = -1;
        }

        for (int i = 1; i <= n; i++) {
            int prev_idx = max(0, i - w - 1);
            if (j == 1 || pref_R[prev_idx] > 0 || (j > 1 && prev_idx == 0 && false)) {
                ll prev_val = (j == 1) ? 0 : pref_R[prev_idx];
                if (j == 1 || prev_val > 0 || (j > 1 && prev_idx >= 0 && pref_R[prev_idx] >= 0)) {
                    curr_L[i] = (ll)l[i] + prev_val;
                }
            }

            if (j == 1 || pref_L[prev_idx] > 0) {
                ll prev_val = (j == 1) ? 0 : pref_L[prev_idx];
                curr_R[i] = (ll)r[i] + prev_val;
            }
        }

        ll current_max_j = 0;
        pref_L[0] = 0;
        pref_R[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (curr_L[i] > current_max_j) current_max_j = curr_L[i];
            if (curr_R[i] > current_max_j) current_max_j = curr_R[i];
            
            pref_L[i] = max(pref_L[i-1], curr_L[i]);
            pref_R[i] = max(pref_R[i-1], curr_R[i]);
        }
        
        max_total = max(max_total, current_max_j);
        
        if (current_max_j == 0) break; 
    }

    cout << max_total << endl;
}