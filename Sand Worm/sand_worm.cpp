#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// กำหนดค่าคงที่เพื่อให้ง่ายต่อการแก้ไข
const int MAX = 705;
const int MAX_COMP = 500005;

int R, C, K;
int north[MAX][MAX], south[MAX][MAX];
bool visN[MAX][MAX];
int compID[MAX][MAX];
int compSize[MAX_COMP];

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

// ฟังก์ชันตรวจสอบขอบเขตตาราง
bool isValid(int r, int c) {
    return (r >= 1 && r <= R && c >= 1 && c <= C);
}

// --- ฟังก์ชัน BFS สำหรับซีกโลกเหนือ ---
// คืนค่าจำนวนช่องทั้งหมดที่เดินไปถึงได้
int bfsNorth(int startR, int startC) {
    if (north[startR][startC] == 1) return 0;

    int count = 0;
    queue<pair<int, int>> q;
    
    q.push({startR, startC});
    visN[startR][startC] = true;
    
    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        count++;

        for (int i = 0; i < 4; i++) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];
            if (isValid(nr, nc) && !visN[nr][nc] && north[nr][nc] == 0) {
                visN[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return count;
}

// --- ฟังก์ชัน BFS สำหรับซีกโลกใต้ (Flood Fill) ---
// ระบุ ID ให้กับกลุ่มช่องว่าง และคืนค่าขนาดของกลุ่มนั้น
int bfsSouth(int startR, int startC, int id) {
    int size = 0;
    queue<pair<int, int>> q;

    q.push({startR, startC});
    compID[startR][startC] = id;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        size++;

        for (int i = 0; i < 4; i++) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];
            if (isValid(nr, nc) && south[nr][nc] == 0 && compID[nr][nc] == 0) {
                compID[nr][nc] = id;
                q.push({nr, nc});
            }
        }
    }
    return size;
}

int main() {
    // เพิ่มความเร็วในการ Input/Output
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C >> K;

    // รับข้อมูลซีกโลกเหนือ
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) cin >> north[i][j];
    }
    // รับข้อมูลซีกโลกใต้
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) cin >> south[i][j];
    }

    // 1. หาพื้นที่ที่เดินได้ในซีกโลกเหนือ
    int totalNorth = bfsNorth(1, 1);

    // 2. จัดกลุ่มพื้นที่ในซีกโลกใต้ (Connected Components)
    int currentID = 0;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (south[i][j] == 0 && compID[i][j] == 0) {
                currentID++;
                compSize[currentID] = bfsSouth(i, j, currentID);
            }
        }
    }

    // 3. ตรวจสอบหนอนทรายและหาขนาดกลุ่มใต้ดินที่ใหญ่ที่สุดที่ไปถึงได้
    int maxSouthReach = 0;
    for (int i = 0; i < K; i++) {
        int r, c;
        cin >> r >> c;
        // เงื่อนไข: สมชายต้องไปถึงช่องนั้นในซีกเหนือ และช่องนั้นในซีกใต้ต้องไม่ใช่พายุ
        if (visN[r][c] && south[r][c] == 0) {
            int id = compID[r][c];
            maxSouthReach = max(maxSouthReach, compSize[id]);
        }
    }

    // ผลลัพธ์คือ จำนวนช่องซีกเหนือ + กลุ่มที่ใหญ่ที่สุดที่เลือกข้ามไปในซีกใต้
    cout << totalNorth + maxSouthReach << endl;

    return 0;
}