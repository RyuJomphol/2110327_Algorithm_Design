#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int board[75][75];
int target[75][75];
bool locked[75][75];
int sr, sc; // ตำแหน่งปัจจุบันของช่องว่าง (-1)
string total_moves = "";

// ทิศทางการเดินของช่องว่าง (-1)
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// แปลงทิศทางของช่องว่างไปเป็นคำสั่งตามกฎ:
// ช่องว่างขึ้น (UP, dr=-1) -> กระเบื้องเลื่อนลง (D)
// ช่องว่างลง (DOWN, dr=1) -> กระเบื้องเลื่อนขึ้น (U)
// ช่องว่างซ้าย (LEFT, dc=-1) -> กระเบื้องเลื่อนขวา (R)
// ช่องว่างขวา (RIGHT, dc=1) -> กระเบื้องเลื่อนซ้าย (L)
char move_char[] = {'D', 'U', 'R', 'L'};

// ฟังก์ชันเข้ารหัสและถอดรหัส State ให้กลายเป็น 1D index
inline int get_id(int tr, int tc, int csr, int csc) {
    return ((tr * N + tc) * N + csr) * N + csc;
}

inline void decode_id(int id, int &tr, int &tc, int &csr, int &csc) {
    csc = id % N; id /= N;
    csr = id % N; id /= N;
    tc = id % N; id /= N;
    tr = id;
}

int main() {
    // ปรับปรุงประสิทธิภาพ I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            cin >> board[r][c];
            locked[r][c] = false;
            if (board[r][c] == -1) {
                sr = r;
                sc = c;
            }
        }
    }

    for (int r = 0; r < N - 2; ++r) {
        for (int c = 0; c < N - 2; ++c) {
            cin >> target[r][c];
        }
    }

    // กำหนดขนาด State Space สูงสุดที่เป้นไปได้
    int MAX_STATES = N * N * N * N;
    // ใช้ pmove แค่ 1 Byte ต่อ State เพื่อประหยัด Memory และรันได้ไว
    vector<char> pmove(MAX_STATES, 0); 
    vector<int> visited_nodes;
    visited_nodes.reserve(1000000);

    // แก้ไขทีละช่องในพื้นที่เป้าหมาย (จากบนลงล่าง ซ้ายไปขวา)
    for (int r = 1; r <= N - 2; ++r) {
        for (int c = 1; c <= N - 2; ++c) {
            int needed_color = target[r - 1][c - 1];

            // หากช่องนั้นมีสีตรงอยู่แล้ว ให้ล็อคและข้ามไปได้เลย
            if (board[r][c] == needed_color) {
                locked[r][c] = true;
                continue;
            }

            // หาตัวเลือกแผ่นกระเบื้องที่เป็นไปได้ทั้งหมดที่สีตรง และยังไม่ถูกล็อค
            vector<pair<int, int>> candidates;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (board[i][j] == needed_color && !locked[i][j]) {
                        candidates.push_back({i, j});
                    }
                }
            }

            queue<int> q;
            visited_nodes.clear();

            // เริ่มต้น State จากแผ่นตัวเลือกทุกแผ่นพร้อมกัน (Multi-source)
            for (auto cand : candidates) {
                int id = get_id(cand.first, cand.second, sr, sc);
                pmove[id] = 'X'; // กำหนด 'X' เพื่อระบุว่าเป็น State เริ่มต้น
                q.push(id);
                visited_nodes.push_back(id);
            }

            int target_id = -1;

            // State-Space BFS
            while (!q.empty()) {
                int u = q.front();
                q.pop();

                int tr, tc, cur_sr, cur_sc;
                decode_id(u, tr, tc, cur_sr, cur_sc);

                // หากกระเบื้องเป้าหมายมาถึงจุดหมายที่ต้องการแล้ว
                if (tr == r && tc == c) {
                    target_id = u;
                    break;
                }

                // ทดลองเดินช่องว่าง (-1) ไปทั้ง 4 ทิศทาง
                for (int i = 0; i < 4; ++i) {
                    int nsr = cur_sr + dr[i];
                    int nsc = cur_sc + dc[i];

                    // เช็คว่าไม่ออกนอกขอบ และไม่ทับช่องที่ถูกล็อคแล้ว
                    if (nsr >= 0 && nsr < N && nsc >= 0 && nsc < N && !locked[nsr][nsc]) {
                        int ntr = tr, ntc = tc;
                        
                        // หากช่องว่างเดินไปทับตำแหน่งที่กระเบื้องอยู่ (เกิดการสลับที่)
                        if (nsr == tr && nsc == tc) {
                            ntr = cur_sr;
                            ntc = cur_sc;
                        }
                        
                        int v = get_id(ntr, ntc, nsr, nsc);
                        
                        // หากเป็น State ใหม่ที่ยังไม่เคยสำรวจ
                        if (pmove[v] == 0) {
                            pmove[v] = move_char[i];
                            q.push(v);
                            visited_nodes.push_back(v);
                        }
                    }
                }
            }

            // แกะรอยเส้นทาง (Path Reconstruction) โดยย้อนกลับจากเป้าหมาย
            if (target_id != -1) {
                string path = "";
                int curr = target_id;
                
                while (true) {
                    char m = pmove[curr];
                    if (m == 'X') break; // เจอจุดเริ่มต้นแล้ว
                    path += m;

                    int tr, tc, cur_sr, cur_sc;
                    decode_id(curr, tr, tc, cur_sr, cur_sc);

                    int dir = -1;
                    for (int i = 0; i < 4; ++i) {
                        if (move_char[i] == m) {
                            dir = i; 
                            break;
                        }
                    }

                    // ย้อนตำแหน่งของช่องว่าง
                    int prev_sr = cur_sr - dr[dir];
                    int prev_sc = cur_sc - dc[dir];

                    // ย้อนตำแหน่งของกระเบื้อง (เช็คว่ารอบนั้นเกิดการสลับที่หรือไม่)
                    int prev_tr = tr;
                    int prev_tc = tc;
                    if (tr == prev_sr && tc == prev_sc) {
                        prev_tr = cur_sr;
                        prev_tc = cur_sc;
                    }

                    curr = get_id(prev_tr, prev_tc, prev_sr, prev_sc);
                }
                
                reverse(path.begin(), path.end());
                total_moves += path;

                // นำเส้นทางมาอัปเดตในกระดานจริง
                for (char m : path) {
                    int dir = -1;
                    for(int i = 0; i < 4; i++) if(move_char[i] == m) dir = i;
                    int nsr = sr + dr[dir];
                    int nsc = sc + dc[dir];
                    swap(board[sr][sc], board[nsr][nsc]);
                    sr = nsr; sc = nsc;
                }
            }

            // ทำความสะอาด Memory เพียงแค่จุดที่เคยเดินผ่านไป (O(Visited) ทำให้รันไวกว่า memset มาก)
            for (int v : visited_nodes) {
                pmove[v] = 0;
            }

            locked[r][c] = true;
        }
    }

    // ยืนยันคำตอบ
    total_moves += "S";
    cout << total_moves << "\n";

    return 0;
}