#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 5005;

int N, P;
vector<int> g[MAXN], gr[MAXN];
bool visited[MAXN];
stack<int> st;
int comp[MAXN]; // component id
int compSize[MAXN];
int compCnt = 0;

void dfs1(int u) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v]) dfs1(v);
    }
    st.push(u);
}

void dfs2(int u, int id) {
    comp[u] = id;
    compSize[id]++;
    for (int v : gr[u]) {
        if (comp[v] == -1) dfs2(v, id);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> P;

    for (int i = 0; i < P; i++) {
        int A, B;
        cin >> A >> B;
        g[A].push_back(B);
        gr[B].push_back(A);
    }

    for(int i = 0; i < N; i++) {
        if (!visited[i]) dfs1(i);
    }

    memset(comp, -1, sizeof(comp));

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (comp[u] == -1) {
            dfs2(u, compCnt++);
        }
    }

    vector<vector<int>> dag(compCnt);
    vector<int> indeg(compCnt, 0);

    for (int u = 0; u < N; u++) {
        for (int v : g[u]) {
            if (comp[u] != comp[v]) {
                dag[comp[u]].push_back(comp[v]);
            }
        }
    }

    for (int u = 0; u < compCnt; u++) {
        for (int v : dag[u]) {
            indeg[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < compCnt; i++) {
        if (indeg[i] == 0) q.push(i);
    }

    vector<int> result;

    while (!q.empty()) {
        int sz = q.size();
        int totalStudents = 0;

        for (int i = 0; i < sz; i++) {
            int u = q.front(); q.pop();
            totalStudents += compSize[u];

            for (int v : dag[u]) {
                indeg[v]--;
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        result.push_back(totalStudents);
    }

    for (int x : result) {
        cout << x << " ";
    }
    cout << "\n";
}