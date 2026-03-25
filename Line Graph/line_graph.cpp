#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e;
    cin >> v >> e;

    vector<vector<int>> adj(v);

    for (int i = 0 ; i < e ; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a); 
    }

    vector<bool> visited(v, false);
    int answer = 0;

    for (int i = 0; i < v; i++) {
        if (visited[i]) continue;

        queue<int> q;
        q.push(i);
        visited[i] = true;

        int nodeCount = 0;
        int edgeCount = 0;
        bool ok = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            nodeCount++;

            int deg = adj[u].size();
            if (deg > 2) ok = false;

            edgeCount += deg;

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        edgeCount /= 2;

        if (ok && edgeCount == nodeCount - 1) {
            answer++;
        }
    }

    cout << answer << "\n";
}