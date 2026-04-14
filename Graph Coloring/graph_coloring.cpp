#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve(int idx, int m, const vector<vector<int>>& graph, vector<int>& color, const vector<int>& order) {
    if (idx == graph.size()) {
        return true;
    }

    int u = order[idx];
    for (int c = 1; c <= m; c++) {
        bool canColor = true;
        for (int v : graph[u]) {
            if (color[v] == c) {
                canColor = false;
                break;
            }
        }
        if (canColor) {
            color[u] = c;
            if (solve(idx + 1, m, graph, color, order)) {
                return true;
            }
            color[u] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int N, E;
    cin >> N >> E;
    vector<vector<int>> graph(N);
    vector<int> degree(N, 0);
    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }

    vector<int> order(N);
    for (int i = 0; i < N; i++) {
        order[i] = i;
    }
    // Sort vertices by degree in descending order
    sort(order.begin(), order.end(), [&](int a, int b) {
        return degree[a] > degree[b];
    });

    for (int m = 1; m <= N; m++) {
        vector<int> color(N, 0);
        
        bool isColorable = solve(0, m, graph, color, order);

        if (isColorable == true) {
        cout << m << "\n";
        break;
        }
    }
}