#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> town_ids(n);
    for (int i = 0; i < n; ++i) {
        cin >> town_ids[i];
    }

    //Prim
    vector<long long> max_weight(n, -1); // เก็บค่า XOR สูงสุดที่จะเชื่อมเข้ากับกลุ่มที่เลือกแล้ว
    vector<bool> visited(n, false);      // เช็คว่าอำเภอนี้ถูกรวมเข้า Tree หรือยัง
    ull total_beauty = 0;

    max_weight[0] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && (u == -1 || max_weight[v] > max_weight[u])) {
                u = v;
            }
        }

        visited[u] = true;
        total_beauty += max_weight[u];

        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                long long current_xor = town_ids[u] ^ town_ids[v];
                if (current_xor > max_weight[v]) {
                    max_weight[v] = current_xor;
                }
            }
        }
    }
    cout << total_beauty << endl;
}