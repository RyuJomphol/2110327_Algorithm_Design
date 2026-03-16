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
    if (!(cin >> R >> C)) return 0;

    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        cin >> grid[i];
    }

    // กรณีพิเศษ: จุดเริ่มต้นหรือจุดจบถูกบล็อก (โจทย์บอกจุดเริ่มว่างเสมอ แต่เช็คเพื่อความชัวร์)
    if (grid[0][0] == '#' || grid[R - 1][C - 1] == '#') {
        cout << -1 << endl;
        return 0;
    }

    // อาร์เรย์สำหรับเช็คว่าเคยไปที่ช่องนั้นหรือยัง
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    
    // สร้าง Queue สำหรับ BFS และใส่จุดเริ่มต้นลงไป (เริ่มที่ระยะทาง 0)
    queue<Node> q;
    q.push({0, 0, 0});
    visited[0][0] = true;

    // ทิศทางการเดิน 4 ทิศ (ล่าง, บน, ขวา, ซ้าย)
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // ตรวจสอบว่าถึงจุดหมาย (R, C) หรือยัง
        if (current.r == R - 1 && current.c == C - 1) {
            cout << current.dist << endl;
            return 0;
        }

        // ลองเดินไปทิศต่างๆ
        for (int i = 0; i < 4; i++) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];

            // ตรวจสอบเงื่อนไข: อยู่ในขอบเขต, เป็นทางว่าง (.), และยังไม่เคยเดินผ่าน
            if (nr >= 0 && nr < R && nc >= 0 && nc < C &&
                grid[nr][nc] == '.' && !visited[nr][nc]) {
                
                visited[nr][nc] = true;
                q.push({nr, nc, current.dist + 1});
            }
        }
    }

    // ถ้าจบการทำงานใน Queue แล้วยังไม่ถึงจุดหมาย
    cout << -1 << endl;

    return 0;
}