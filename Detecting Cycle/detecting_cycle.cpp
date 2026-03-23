#include <iostream>
#include <vector>

using namespace std;

//DFS
bool hasCycle(int u, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            if (hasCycle(v, u, adj, visited)) return true;
        }
        else if (v != parent) return true; 
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> N >> E;

        //make adj matrix
        vector<vector<int>> adj(N);
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        //make vector check if it's visited before
        vector<bool> visited(N, false);
        bool found = false;

        // check all component
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                if(hasCycle(i, -1, adj, visited)) {
                    found = true;
                }
            }
        }

        if (found) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}