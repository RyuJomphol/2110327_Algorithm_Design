#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> hackTime(k);
    for (int i = 0; i < k; i++) {
        cin >> hackTime[i];
    }

    vector<long long> cost(n);
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    for (int u : hackTime) {
        dist[u] = cost[u];
        pq.push({dist[u], u});
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (int v : adj[u]) {
            long long newDist = dist[u] + cost[v];
            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({dist[v], v});
            }
        }
    }

    long long max_time = 0;
    for (int i = 0; i < n; i++) {
        max_time = max(max_time, dist[i]);
    }

    cout << max_time << "\n";


}