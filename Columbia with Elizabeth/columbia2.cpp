#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

const long long INF = 1e18;

// ทิศทางการเดินปกติ 4 ทิศ
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// ทิศทางการใช้ Tear (ระยะทางไม่เกิน 2 บล็อก ทั้งหมด 12 จุด)
int tear_r[] = {-2, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 2};
int tear_c[] = {0, -1, 0, 1, -2, -1, 1, 2, -1, 0, 1, 0};

int main() {
    // เพิ่มความเร็วในการ I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<vector<long long>> grid(R, vector<long long>(C));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
        }
    }

    // dist[r][c][k] เก็บค่าใช้จ่ายน้อยที่สุด
    vector<vector<vector<long long>>> dist(R, vector<vector<long long>>(C, vector<long long>(3, INF)));
    
    // priority_queue เก็บ pair<cost, tuple<r, c, k>>
    // ใช้ greater เพื่อให้ดึงค่าที่ cost น้อยที่สุดออกมาก่อน
    priority_queue<
        pair<long long, tuple<int, int, int>>, 
        vector<pair<long long, tuple<int, int, int>>>, 
        greater<pair<long long, tuple<int, int, int>>>
    > pq;

    // เริ่มต้นที่ (0, 0) ใช้ Tear 0 ครั้ง ค่าใช้จ่ายเป็น 0
    dist[0][0][0] = 0;
    pq.push({0, {0, 0, 0}});

    while (!pq.empty()) {
        // ใช้ tie หรือดึงค่าแบบปกติออกมา
        auto current = pq.top();
        pq.pop();

        long long cost = current.first;
        int r = get<0>(current.second);
        int c = get<1>(current.second);
        int k = get<2>(current.second);

        if (cost > dist[r][c][k]) continue;

        // 1. เดินแบบปกติ (4 ทิศทาง)
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                if (dist[r][c][k] + grid[nr][nc] < dist[nr][nc][k]) {
                    dist[nr][nc][k] = dist[r][c][k] + grid[nr][nc];
                    pq.push({dist[nr][nc][k], {nr, nc, k}});
                }
            }
        }

        // 2. ใช้ Tear (ถ้ายังใช้ไม่ครบ 2 ครั้ง)
        if (k < 2) {
            for (int i = 0; i < 12; ++i) {
                int nr = r + tear_r[i];
                int nc = c + tear_c[i];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (dist[r][c][k] < dist[nr][nc][k + 1]) {
                        dist[nr][nc][k + 1] = dist[r][c][k];
                        pq.push({dist[nr][nc][k + 1], {nr, nc, k + 1}});
                    }
                }
            }
        }
    }

    // แสดงผลลัพธ์
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            long long min_cost = dist[i][j][0];
            min_cost = min(min_cost, dist[i][j][1]);
            min_cost = min(min_cost, dist[i][j][2]);
            
            cout << min_cost << (j == C - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}