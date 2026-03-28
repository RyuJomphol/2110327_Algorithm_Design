#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> g, gr;
vector<bool> visited;
stack<int> st;
vector<int> comp;

void dfs1(int u) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v]) dfs1(v);
    }
    st.push(u);
}

int dfs2(int u) {
    visited[u] = true;
    int size = 1;
    for (int v : gr[u]) {
        if (!visited[v]) {
            size += dfs2(v);
        }
    }
    return size;
}

int main() {
    int N;
    cin >> N;
    g.resize(N);
    gr.resize(N);

    for(int i = 0; i < N; i++) {
        int M;
        cin >> M;
        while(M--) {
            int v;
            cin >> v;
            g[i].push_back(v);
            gr[v].push_back(i);
        }
    }

    //DFS graph
    visited.assign(N, false);
    for (int i = 0; i < N; i++) {
        if (!visited[i]) dfs1(i);
    }

    //DFS reverse graph
    visited.assign(N, false);
    vector<int> result;

    while(!st.empty()) {
        int u = st.top();
        st.pop();
        if(!visited[u]) {
            int size = dfs2(u);
            result.push_back(size);
        }
    }

    sort(result.begin(), result.end());
    for (int x : result) {
        cout << x << " ";
    }
}