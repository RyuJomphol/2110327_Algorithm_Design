#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int count_friends(int start_node, int N, int K, const vector<vector<int>>& adj) {
    vector<int> dist(N, -1);
    queue<int> q;

    q.push(start_node);
    dist[start_node] = 0;
    int count = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] <= K) {
            count++;
        }

        if (dist[u] == K) continue;

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, E, K;
    cin >> N >> E >> K;

    vector<vector<int>> adj(N);
    for(int i = 0 ; i < E ; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int max_friends = 0;

    for (int i = 0; i < N; i++) {
        int current_friends = count_friends(i, N, K, adj);
        if (current_friends > max_friends) {
            max_friends = current_friends;
        }
    }

    cout << max_friends << endl;
}