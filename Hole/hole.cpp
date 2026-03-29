#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 1002;
const int INF = 1e9;

// ตารางเก็บข้อมูลหลุมและระยะทางที่สั้นที่สุด
bool is_sinkhole[MAX][MAX];
int dist[MAX][MAX];

int dr[] = { -1, 1, 0, 0 }; // ทิศทางการเคลื่อนที่ (ขึ้น, ลง, ซ้าย, ขวา)
int dc[] = { 0, 0, -1, 1 };

struct Node {
    int r, c, d;
    bool operator>(const Node& other) const {
        return d > other.d; // สำหรับ priority_queue ให้เรียงจากน้อยไปมาก
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, a, b;
    cin >> N >> a >> b;

    for (int i = 0; i < N; ++i) {
        int r, c;
        cin >> r >> c;
        is_sinkhole[r][c] = true; // ทำเครื่องหมายตำแหน่งหลุม
    }

    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j <= 1000; ++j) {
            dist[i][j] = INF; // กำหนดระยะทางเริ่มต้นเป็นอนันต์
        }
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[a][b] = 0; // เริ่มต้นที่ตำแหน่ง (a, b)
    pq.push({a, b, 0});

    int min_distance = INF;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int r = current.r;
        int c = current.c;
        int d = current.d;

        if (d > dist[r][c]) continue; // ข้ามถ้าระยะทางที่ได้มากกว่าในตาราง

        if (r == 1 || r == 1000 || c == 1 || c == 1000) {
            min_distance = d;
            break;
        } // ถ้าเจอหลุม ให้เติมน้ำและเพิ่มระยะทาง

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 1 && nr <= 1000 && nc >= 1 && nc <= 1000) {
                int new_dist = d + (is_sinkhole[nr][nc] ? 1 : 0); // ถ้าเป็นหลุม เพิ่มระยะทาง

                if (new_dist < dist[nr][nc]) {
                    dist[nr][nc] = new_dist;
                    pq.push({nr, nc, new_dist});
                }
            }
        }
    }

    cout << min_distance << endl;
}