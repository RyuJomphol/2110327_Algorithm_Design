#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int weight;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    int v;
    cin >> v;

    vector<int> start_node(k);
    for (int i = 0; i < k; i++) {
        cin >> start_node[i];
    }

    vector<vector<Edge>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[b].push_back({a, w});
    }

    vector<long long> dist(n, INF);
    vector<bool> in_queue(n, false);
    queue<int> q;

    dist[v] = 0;
    q.push(v);
    in_queue[v] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                if (!in_queue[edge.to]) {
                    q.push(edge.to);
                    in_queue[edge.to] = true;
                }
            }
        }
    }

    long long min_dist = INF;
    for (int node : start_node) {
        if (dist[node] < min_dist) {
            min_dist = dist[node];
        }
    }

    cout << min_dist << endl;
}