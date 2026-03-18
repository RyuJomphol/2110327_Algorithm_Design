#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos {
    int r, c, dist;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, K;
    cin >> R >> C >> K;
    vector<vector<int>> grid(R, vector<int>(C)); //เก็บตาราง
    vector<vector<int>> dist(R, vector<int>(C, -1)); //เก็บว่าไปถึงยังนะ
    queue<Pos> q;

    for (int i = 0; i < R; i++) { //หาจุดที่เป็นพื้นดิน
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                q.push({i, j, 0});
                dist[i][j] = 0;
            }
        }
    }

    int dr[] = {-1, 1, 0, 0}; //เดินบน ล่าง
    int dc[] = {0, 0, -1, 1}; //เดินซ้าย ขวา

    //Start BFS
    while (!q.empty()) {
        Pos curr = q.front();
        q.pop();

        if (curr.dist >= K) continue;

        for (int i = 0; i < 4; i++) { //เคลื่อนที่
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && dist[nr][nc] == -1) {
                dist[nr][nc] = curr.dist + 1; 

                if(grid[nr][nc] == 0) { //เปลี่ยน grid 0 -> 2
                    grid[nr][nc] = 2;
                }

                q.push({nr, nc, dist[nr][nc]}); //ขยายต่อ
            }
        }
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}
