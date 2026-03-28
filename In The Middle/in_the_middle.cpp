#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 250005;
const int INF = 1e9;

vector<int> adj[MAXN];
int d1[MAXN], d2[MAXN], d3[MAXN];

void bfs(int start, int dist[], int n) {
    for (int i = 1; i <= n; i++) dist[i] = INF;

    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int t1, t2, t3;
    cin >> t1 >> t2 >> t3;

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        while(k--) {
            int v;
            cin >> v;
            adj[i].push_back(v);
        }
    }

    bfs(t1, d1, n);
    bfs(t2, d2, n);
    bfs(t3, d3, n);

    int min_max_dist = INF;

    for (int i = 1; i <= n; i++) {
        if (d1[i] != INF && d2[i] != INF && d3[i] != INF) {
            int current_max = max({d1[i], d2[i], d3[i]});
            min_max_dist = min(min_max_dist, current_max);
        }
    }

    cout << min_max_dist << endl;
}