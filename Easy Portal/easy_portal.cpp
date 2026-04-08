#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int INF = 1e9;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    // คำแนะนำจากโจทย์เพื่อความรวดเร็ว [cite: 56]
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<string> grid(N);
    int start_r, start_c, br = -1, bc = -1, wr = -1, wc = -1;

    for (int i = 0; i < N; i++) {
        cin >> grid[i]; // อ่านทั้งบรรทัดเป็น string [cite: 57]
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'S') { start_r = i; start_c = j; }
            if (grid[i][j] == 'B') { br = i; bc = j; }
            if (grid[i][j] == 'W') { wr = i; wc = j; }
        }
    }

    vector<vector<int>> dist(N, vector<int>(M, INF));
    queue<pair<int, int>> q;

    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        if (grid[r][c] == 'T') {
            cout << dist[r][c] << endl;
            return 0;
        }

        // --- กรณีวาร์ป: ถ้าอยู่ที่ B และมี W ให้ลองวาร์ป ---
        if (grid[r][c] == 'B' && wr != -1) {
            if (dist[wr][wc] > dist[r][c] + 1) {
                dist[wr][wc] = dist[r][c] + 1; // เสียเวลาวาร์ป 1 หน่วย 
                q.push({wr, wc});
            }
        }

        // --- กรณีเดินปกติ 4 ทิศทาง ---
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#') {
                if (dist[nr][nc] > dist[r][c] + 1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    cout << -1 << endl; // ถ้าหาทางไปไม่ถึง [cite: 37, 52]
    return 0;
}