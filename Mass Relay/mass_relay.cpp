#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    int num_sets;

    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        num_sets = n;
    }

    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    bool unite(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            parent[b] = a;
            num_sets--;
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end());

    vector<int> ans(N + 1, 0);
    DSU dsu(N);

    int current_k = 0;

    for(int i = 0; i < M; i++) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            current_k = edges[i].w;

            if (dsu.num_sets <= N) {
                ans[dsu.num_sets] = current_k;
            }
        }
    }

    for (int i = N - 1; i >= 1; i--) {
        if (ans[i] == 0) ans[i] = ans[i + 1];
        else ans[i] = max(ans[i], ans[i+1]);
    }

    while (Q--) {
        int D;
        cin >> D;
        if (D >= N) cout << 0 << "\n";
        else cout << ans[D] << "\n";
    }
    


}