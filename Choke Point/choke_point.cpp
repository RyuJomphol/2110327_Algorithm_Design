#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> adj;
vector<long long> importance;
vector<int> subtree_size;

// ฟังก์ชัน DFS เพื่อหาขนาด Subtree และคำนวณ Importance
int dfs(int u, int p) {
    subtree_size[u] = 1; // นับตัวเองก่อน
    long long sum_squares = 0; // เก็บผลรวมของ S_i^2 เพื่อใช้ในสูตรลดรูป
    int total_children_size = 0;

    for (int v : adj[u]) {
        if (v != p) {
            int size_v = dfs(v, u);
            subtree_size[u] += size_v;
            total_children_size += size_v;
            
            sum_squares += (long long)size_v * size_v;
        }
    }

    // ขนาดของกลุ่มย่อยที่อยู่ "ด้านบน" ของโหนด u (ทิศที่วิ่งไปหา root เดิม)
    int upper_size = n - subtree_size[u];
    if (upper_size > 0) {
        sum_squares += (long long)upper_size * upper_size;
    }

    // สูตรคำนวณ Importance: [ (n-1)*n - sum(S_i^2 - S_i) ] / 2
    // ซึ่งแปลงรูปทางคณิตศาสตร์ให้เขียนง่ายขึ้นได้เป็นแบบด้านล่างนี้ครับ:
    long long imp = ((long long)(n - 1) * n - (sum_squares - (n - 1))) / 2;
    importance[u] = imp;

    return subtree_size[u];
}

int main() {
    // เพิ่มความเร็วในการ I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    adj.resize(n);
    importance.resize(n, 0);
    subtree_size.resize(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // เริ่มทำ DFS จากโหนด 0 (กำหนดให้ parent เป็น -1)
    dfs(0, -1);

    // แสดงผลลัพธ์
    for (int i = 0; i < n; ++i) {
        cout << importance[i] << "\n";
    }

    return 0;
}