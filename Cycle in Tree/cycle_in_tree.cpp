#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        deg[x]++;
        deg[y]++;
    }
    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (deg[i] == 1) {
            q.push(i);
        }
    }

    vector<bool> removed(n, false);

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        removed[u] = true;

        for (int v : adj[u]) {
            if (!removed[v]) {
                deg[v]--;
                if (deg[v] == 1) {
                    q.push(v);
                }
            }
        }
    }

    int cycle_nodes = 0;
    for (int i = 0; i < n; i++) {
        if (!removed[i]) {
            cycle_nodes++;
        }
    }

    cout << cycle_nodes << "\n";

} 