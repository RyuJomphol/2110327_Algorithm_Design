#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int main() {
    int r, c, T;
    cin >> r >> c >> T;

    vector<vector<int>> grid(r, vector<int>(c));
    vector<vector<int>> dist(r, vector<int>(c, -1));
    queue<pair<int,int>> q;

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    //direction
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while(!q.empty()) {
        auto [r0, c0] = q.front();
        q.pop();

        for(int k = 0; k < 4; k++) {
            int nr = r0 + dr[k];
            int nc = c0 + dc[k];

            if (nr < 0 || nr >= r || nc < 0 || nc >= c) continue;
            if (grid[nr][nc] == 2) continue; // Mountain
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r0][c0] + 1;
            q.push({nr, nc});
        }
    }

    int ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] != 2 && dist[i][j] != -1 && dist[i][j] <= T) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
}