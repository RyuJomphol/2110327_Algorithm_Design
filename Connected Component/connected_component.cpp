#include <iostream>
#include <vector>

using namespace std;

const int MAX = 10005;
vector<int> adj[MAX];    // Adjacency List
bool visited[MAX];      // Visited array to keep track of visited vertices

void dfs(int node) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int v, e;
    cin >> v >> e;

    for (int i = 0; i < e; ++i) {
        int u, w;
        cin >> u >> w;
        // Ensure that we only add edges in one direction to avoid duplicates
        if (u <= v && w <= v) {
            adj[u].push_back(w);
            adj[w].push_back(u);
        }
    }

    int component_count = 0;
    for (int i = 1; i <= v; ++i) {
        if (!visited[i]) {
            dfs(i);
            component_count++;
        }
    }

    cout << component_count << endl;

}