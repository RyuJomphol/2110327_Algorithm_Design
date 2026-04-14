#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct State {
    ll candidates;
    int current_sum;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> B(n);
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    vector<ll> adj(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1 && i != j) {
                adj[i] |= (1LL << j);
            }
        }
    }

    int max_weight = 0;
    vector<State> stack;

    ll all_candidates = (1LL << n) - 1;
    stack.push_back({all_candidates, 0});

    while (!stack.empty()) {
        State state = stack.back();
        stack.pop_back();

        if (state.candidates == 0) {
            max_weight = max(max_weight, state.current_sum);
            continue;
        }

        int potential_sum = state.current_sum;
        for (int i = 0; i < n; i++) {
            if (state.candidates & (1LL << i)) {
                potential_sum += B[i];
            }
        }
        if (potential_sum <= max_weight) {
            continue;
        }

        int v = 0;
        while ((state.candidates & (1LL << v)) == 0) {
            v++;
        }

        ll v_mask = (1LL << v);

        // กรณี A: "ไม่เลือก" พนักงาน v เข้าทีม
        // แค่เอา v ออกจากเซต candidates แล้วไปต่อ
        stack.push_back({state.candidates ^ v_mask, state.current_sum});

        // กรณี B: "เลือก" พนักงาน v เข้าทีม
        // 1. เพิ่มน้ำหนัก v เข้าไปใน current_sum
        // 2. คนที่จะเลือกต่อได้ ต้องเป็นเพื่อนกับ v เท่านั้น (candidates & adj[v])
        stack.push_back({(state.candidates ^ v_mask) & adj[v], state.current_sum + B[v]});
    }

    cout << max_weight << endl;
}