#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MOD = 16777216;

int solve_bfs(int start_x) {
    if (start_x == 0) return 0;

    // เก็บระยะทางจาก x เริ่มต้น (ใช้ -1 เพื่อบอกว่ายังไม่เคยไปถึง)
    vector<int> dist(MOD, -1);
    queue<int> q;

    q.push(start_x);
    dist[start_x] = 0;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        // ลอง Operation 1: (x + 1)
        int next1 = (curr + 1) % MOD;
        if (next1 == 0) return dist[curr] + 1;
        if (dist[next1] == -1) {
            dist[next1] = dist[curr] + 1;
            q.push(next1);
        }

        // ลอง Operation 2: (x * 2)
        int next2 = (curr * 2) % MOD;
        if (next2 == 0) return dist[curr] + 1;
        if (dist[next2] == -1) {
            dist[next2] = dist[curr] + 1;
            q.push(next2);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    long long x;
    cin >> x;

    int result = solve_bfs(x % MOD);
    cout << result << endl;

    return 0;
}