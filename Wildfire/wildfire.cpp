#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> b(n);
    long long sum = 0;

    for (int i = 0 ; i < n ;i++) {
        cin >> b[i];
        sum += b[i];
    }

    vector<int> fire(k);
    for (int i = 0; i < k; i++) {
        cin >> fire[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    vector<bool> burnt(n, false);

    for (int day = 0; day < m; day++) {
        int start = fire[day];

        if (!burnt[start]) {
            queue<int> q;
            q.push(start);
            burnt[start] = true;
            sum -= b[start];

            while(!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (!burnt[v]) {
                        burnt[v] = true;
                        sum -= b[v];
                        q.push(v);
                    }
                }
            }
        }
        cout << sum << " "; 
    }
}