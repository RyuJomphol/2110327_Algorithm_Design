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

        int v = __builtin_ctzll(state.candidates);
        ll new_candidates = state.candidates & ~adj[v] & ~(1LL << v);

        stack.push_back({state.candidates & ~(1LL << v), state.current_sum});
        stack.push_back({new_candidates, state.current_sum + B[v]});
    }

    cout << max_weight << endl;
}