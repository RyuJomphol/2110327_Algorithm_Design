#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e;
    cin >> n >> e;

    vector<vector<int>> pre(n + 1);

    for (int i = 0 ; i < e; i++) {
        int a, b;
        cin >> a >> b;
        pre[b].push_back(a);
    }

    for(int t = 0; t < 5; t++) {
        vector<int> plan(n);
        for (int i = 0 ; i < n; i++) {
            cin >> plan[i];
        }

        vector<bool> visited(n + 1, false);
        bool ok = true;

        for (int i = 0; i < n; i++) {
            int step = plan[i];

            // เช็ค prerequisite
            for (int p : pre[step]) {
                if (!visited[p]) {
                    ok = false;
                    break;
                }
            }

            if (!ok) break;

            visited[step] = true;
        }
        if (ok) cout << "SUCCESS\n";
        else cout << "FAIL\n";
    }
}