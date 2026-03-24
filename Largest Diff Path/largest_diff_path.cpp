#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAXN = 2005;
int c[MAXN];          // เก็บน้ำหนักของแต่ละปม
int min_val[MAXN];    // เก็บค่า c ที่น้อยที่สุดที่เดินทางมาถึงปมนั้นได้
int in_degree[MAXN];  // นับจำนวนเส้นเชื่อมที่เข้าหาปม
vector<int> adj[MAXN]; // Adjacency List เก็บโครงสร้างกราฟ

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> c[i];
        min_val[i] = c[i];
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }

    queue<int> q;
    int max_diff = 0;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        max_diff = max(max_diff, c[curr] - min_val[curr]);

        for (int next : adj[curr]) {
            min_val[next] = min(min_val[curr], min_val[next]);
            in_degree[next]--;
            if(in_degree[next] == 0) {
                q.push(next);
            } 
        }
    }

    cout << max_diff << endl;
}