#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Edge> edges;
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            int w;
            cin >> w;
            edges.push_back({i, j, w});
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu(N);
    long long min_cost = 0;
    int edges_count = 0;

    for (auto edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            min_cost += edge.weight;
            edges_count++;
            // ถ้าเลือกครบ N-1 เส้นแล้ว คือเชื่อมครบทุกโหนด
            if (edges_count == N - 1) break;
        }
    }

    cout << min_cost << endl;
}

