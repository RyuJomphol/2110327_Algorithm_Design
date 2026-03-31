#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    cin >> R >> C;

    // เปลี่ยนมาใช้ vector 2 มิติแบบ int แทน string เพื่อความชัวร์ในการอ่านข้อมูล
    vector<vector<int>> grid(R, vector<int>(C));
    vector<pair<int, int>> starts;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                starts.push_back({i, j});
            }
        }
    }

    int n = starts.size();
    vector<vector<vector<int>>> dist(n, vector<vector<int>>(R, vector<int>(C, INF)));

    // ทำ BFS สำหรับแต่ละจุดเริ่มต้น
    for (int i = 0; i < n; ++i) {
        queue<pair<int, int>> q;
        int sr = starts[i].first;
        int sc = starts[i].second;

        dist[i][sr][sc] = 0;
        q.push({sr, sc});

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // ตรวจสอบว่าอยู่ในขอบเขต และไม่ใช่สิ่งกีดขวาง (ไม่ใช่ 1)
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != 1) {
                    if (dist[i][nr][nc] == INF) {
                        dist[i][nr][nc] = dist[i][r][c] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
    }

    int count = 0;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            // 1. แก้ไขจุดเดิม: ต้องเช็กช่องที่ไม่ใช่สิ่งกีดขวาง (grid[r][c] != 1)
            if (grid[r][c] != 1) { 
                int max_d = -1;
                int min_d = INF;
                bool reachable = true;

                for (int i = 0; i < n; i++) {
                    if (dist[i][r][c] == INF) {
                        reachable = false;
                        break;
                    }
                    max_d = max(max_d, dist[i][r][c]);
                    min_d = min(min_d, dist[i][r][c]);
                }

                if (reachable && (max_d - min_d <= 1)) {
                    count++;
                }
            }
        }
    }

    cout << count << "\n";
    return 0;
}