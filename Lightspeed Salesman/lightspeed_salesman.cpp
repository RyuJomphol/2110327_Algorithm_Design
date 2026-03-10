#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// ฟังก์ชันหาความยาวเส้นทางที่สั้นที่สุดบนวงกลมแบบ "ไม่มี" Portal
ll get_normal_dist(int u, int v, int M, const vector<ll>& prefix_sum) {
    if (u == v) return 0;
    int start = min(u, v);
    int end = max(u, v);
    
    // ระยะทางตามเข็มนาฬิกา
    ll dist1 = prefix_sum[end] - prefix_sum[start];
    // ระยะทางทวนเข็มนาฬิกา
    ll dist2 = prefix_sum[M] - dist1;
    
    return min(dist1, dist2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<int> sequence(M);
    for (int i = 0; i < M; i++) {
        cin >> sequence[i];
    }

    vector<ll> t(M);
    vector<ll> prefix_sum(M + 1, 0);
    for (int i = 0; i < M; ++i) {
        cin >> t[i];
        prefix_sum[i + 1] = prefix_sum[i] + t[i];
    }

    for (int d = 0; d < N; ++d) {
        int A, B;
        cin >> A >> B;

        ll total_day_dist = 0;

        for (int i = 0; i < M; ++i) {
            int u = sequence[i];
            int v = sequence[(i + 1) % M];

                // ไม่ใช้ Portal
            ll d_direct = get_normal_dist(u, v, M, prefix_sum);

                // ผ่าน Portal (u -> A ->วาร์ป-> B -> v)
            ll d_via_portal1 = get_normal_dist(u, A, M, prefix_sum) + get_normal_dist(B, v, M, prefix_sum);

                // ผ่าน Portal (u -> B ->วาร์ป-> A -> v)
            ll d_via_portal2 = get_normal_dist(u, B, M, prefix_sum) + get_normal_dist(A, v, M, prefix_sum);

            total_day_dist += min({d_direct, d_via_portal1, d_via_portal2});
        }
        cout << total_day_dist << "\n";
    }
}