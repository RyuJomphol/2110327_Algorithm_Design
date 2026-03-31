#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 2e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<vector<pair<int, int>>> adj(N + 1);

    for (int i = 1 ; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int w;
            cin >> w;
            if (w > 0) {
                adj[i].push_back({j, w});
            }
        }
    }

    vector<int> dist(N + 1, INF);
    dist[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    int maxDist = -1;
    bool disconnected = false;
    for (int i = 2; i <= N; i++) {
        if (dist[i] == INF) {
            disconnected = true;
            break;
        } else {
            maxDist = max(maxDist, dist[i]);
        }
    }

    if (disconnected) {
        cout << -1 << "\n";
    } else {
        cout << maxDist << "\n";
    }
}