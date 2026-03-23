#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
int dr[] = {-1, 1, 0, 0}; // สำหรับเลื่อน 4 ทิศ
int dc[] = {0, 0, -1, 1};

struct Node {
    int r, c, cost;
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;

    vector<vector<int>> fee(R, vector<int>(C));
    vector<vector<int>> dist(R, vector<int>(C, INF));

    for (int i = 0 ; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> fee[i][j];
        }
    }

    // Dijkstra's Algorithm
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[0][0] = 0;
    pq.push({0,0,0});

    while(!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        int r = curr.r;
        int c = curr.c;
        int d = curr.cost;

        if (d > dist[r][c]) continue;

        for (int i = 0 ; i < 4 ; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                if (dist[r][c] + fee[nr][nc] < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + fee[nr][nc];
                    pq.push({nr, nc, dist[nr][nc]});
                }
            }
        }
    }
    for (int i = 0 ; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << dist [i][j] << " ";
        }
        cout << "\n";
    }
}