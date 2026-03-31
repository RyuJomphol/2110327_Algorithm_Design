#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int dist[705][705];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c12;
    cin >> n >> c12;

    // Initialize distances
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    dist[1][2] = dist[2][1] = c12;

    for (int i = 3; i <= n; i++) {
        int k_i;
        cin >> k_i;

        vector<pair<int, int>> connections;
        for (int j = 0; j < k_i; j++) {
            int t, p;
            cin >> t >> p;
            connections.push_back({t, p});
        }

        for (int k = 1; k < i; k++) {
            for (auto &edge : connections) {
                int t = edge.first, p = edge.second;
                dist[i][k] = min(dist[i][k], dist[t][k] + p);
                dist[k][i] = min(dist[k][i], dist[k][t] + p);
            }
        }

        for (int a = 1; a < i; a++) {
            for (int b = 1; b < i; b++) {
                dist[a][b] = min(dist[a][b], dist[a][i] + dist[i][b]);
            }
        }

        cout << dist[1][2] << " ";
    }
    cout << "\n";
}