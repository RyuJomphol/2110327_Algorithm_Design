#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// ใช้ long long เพราะระยะทางรวมอาจเกิน 2*10^9
const long long INF = 1e18; 

struct Edge {
    int to;
    long long weight;
};

struct Node {
    int id;
    long long dist;
    // priority_queue ใน C++ เป็น Max Heap จึงต้องสลับเครื่องหมายเพื่อให้เป็น Min Heap
    bool operator>(const Node& other) const {
        return dist > other.dist;
    }
};

int main() {
    // เพิ่มความเร็วในการ Input/Output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    // ใช้ Adjacency List แทน Matrix เพื่อประหยัดแรม
    vector<vector<Edge>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // ถนน 2 ทิศทาง
    }

    // Dijkstra's Algorithm
    vector<long long> dist(N + 1, INF);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.id;
        long long d = current.dist;

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({edge.to, dist[edge.to]});
            }
        }
    }

    // หาเวลาที่มาถึงพร้อมกันที่เร็วที่สุด (ระยะทางที่ไกลที่สุดจากเมือง 1)
    long long max_dist = 0;
    for (int i = 2; i <= N; i++) {
        if (dist[i] != INF) {
            max_dist = max(max_dist, dist[i]);
        }
    }

    // แสดงคำตอบสำหรับเมือง 2, 3, ..., N
    for (int i = 2; i <= N; i++) {
        // เวลาเริ่ม = เวลาเป้าหมาย - เวลาเดินทาง
        cout << max_dist - dist[i] << "\n";
    }

    return 0;
}