#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
};

const long long INF = 1e18;

// if there are update value just print -1


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, E, s;
    cin >> N >> E >> s;

    vector<Edge> edges;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<long long> dist(N, INF);
    dist[s] = 0;

    for(int i = 1; i <= N - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    vector<long long> check_cycle(N, 0); 
    bool hasNegativeCycle = false;
    for (int i = 1; i <= N; i++) { // ทำ N รอบ
        for (const auto& edge : edges) {
            if (check_cycle[edge.u] + edge.weight < check_cycle[edge.v]) {
                check_cycle[edge.v] = check_cycle[edge.u] + edge.weight;
                if (i == N) hasNegativeCycle = true; // ถ้ามีการเปลี่ยนในรอบที่ N แสดงว่ามี Cycle
            }
        }
    }

    if (hasNegativeCycle) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < N; i++) {
            if (dist[i] >= INF/2) { // ถ้าค่าเข้าใกล้ INF แสดงว่าไปไม่ถึง
                // ในโจทย์บางที่ให้พิมพ์ "INF" แต่ถ้าโจทย์นี้ให้พิมพ์ตัวเลข 
                // ให้เช็กเงื่อนไขโจทย์อีกทีครับ (ตัวอย่างที่ให้มาไม่ได้โชว์กรณีไปไม่ถึง)
                cout << "INF"; 
            } else {
                cout << dist[i];
            }
            if (i < N - 1) cout << " ";
        }
        cout << endl;
    }
}