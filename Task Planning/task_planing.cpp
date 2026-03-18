#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    vector<int> in_degree(N, 0);

    for (int i = 0; i < N; i++) {
        int M;
        cin >> M;
        for (int j = 0; j < M ; j++) {
            int pre;
            cin >> pre;
            adj[pre].push_back(i);
            in_degree[i]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
}