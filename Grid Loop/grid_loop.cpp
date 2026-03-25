#include <iostream>
#include <vector>
#include <map>

using namespace std;

using pii = pair<int,int>;

const int MAXN = 2000005;
int maxCycleLength = 0;
int cycleCount = 0;
vector<pii> dir1 = {
    {0,-1},   // type 1
    {-1,0},   // type 2
    {-1,0},   // type 3
    {0,1},    // type 4
    {1,0},    // type 5
    {0,-1}    // type 6
};

vector<pii> dir2 = {
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {0,-1},
    {-1,0}
};

map<pii,int> nodeId;

vector<int> graph[MAXN];
bool visited[MAXN];

bool dfs(int u, int parent, int length) {
    if (visited[u]) {
        maxCycleLength = max(maxCycleLength, length);
        cycleCount++;
        return true;
    }

    visited[u] = true;

    for (int v : graph[u]) {
        if (v == parent) continue;
        if (dfs(v, u, length + 1)) return true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    cin >> R >> C;

    int idCounter = 1;

    for (int i = 1 ; i <= 2 * R; i += 2) {
        for (int j = 1; j <= 2 * C; j += 2) {
            int type;
            cin >> type;
            type--;

            pii u = {i + dir1[type].first, j + dir1[type].second};
            pii v = {i + dir2[type].first, j + dir2[type].second};

            // assign id
            if (!nodeId[u]) nodeId[u] = idCounter++;
            if (!nodeId[v]) nodeId[v] = idCounter++;

            int uid = nodeId[u];
            int vid = nodeId[v];

            // สร้าง edge
            graph[uid].push_back(vid);
            graph[vid].push_back(uid);
        }
    } 
}