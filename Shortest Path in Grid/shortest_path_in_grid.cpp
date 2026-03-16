#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// สร้าง struct เพื่อเก็บตำแหน่ง (row, col) และระยะทาง (dist)
struct Node {
    int r, c, dist;
};

int main() {
    int R, C;
    cin >> R >> C;

    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        cin >> grid[i];
    }

    vector<vector<bool>> visited(R, vector<bool>(C, false)); // สร้างตาราง visited เพื่อเช็คว่าตำแหน่งไหนถูกเยี่ยมชมแล้ว
    visited[0][0] = true; // เริ่มต้นที่ตำแหน่ง (0, 0)

    // สร้าง queue สำหรับ BFS
    queue<Node> q;
    q.push({0, 0, 0}); // เริ่มต้นที่ตำแหน่ง (0, 0) และระยะทางเริ่มต้นเป็น 0

    int dr[] = {1, -1, 0, 0}; // การเคลื่อนที่ในแนวตั้ง (ลง, ขึ้น)
    int dc[] = {0, 0, 1, -1}; // การเคลื่อนที่ในแนวนอน (ขวา, ซ้าย)

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // ตรวจสอบว่าถึงจุดหมายแล้วหรือไม่
        if (current.r == R - 1 && current.c == C - 1) {
            cout << current.dist << endl;
            return 0;
        }

        // ตรวจสอบตำแหน่งที่สามารถเคลื่อนที่ได้
        for (int i = 0; i < 4; i++) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];

            // ตรวจสอบขอบเขตของตารางและว่าตำแหน่งนั้นไม่ถูกเยี่ยมชมแล้ว
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc] && grid[nr][nc] == '.') {
                visited[nr][nc] = true;
                q.push({nr, nc, current.dist + 1});
            }
        }
    }

    cout << "-1" << endl;
    return 0;
}