#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
int N;

long long solve(int mask, int last, const vector<vector<int>>& graph, vector<vector<long long>>& memo) {
    // Base Case: ถ้าไปครบทุกเมืองแล้ว
    if (mask == (1 << N) - 1) {
        //
        if (last == N - 1) return 0;
        return -INF;
    }

    // ถ้ายังไปไม่ครบทุกเมือง แต่ดันมาถึงเมือง N แล้ว ถือว่าไม่สำเร็จ
    if (last == N - 1) {
        return -INF;
    }

    // Memoization
    if (memo[mask][last] != -1) {
        return memo[mask][last];
    }

    long long best = -INF;

    for (int next = 0; next < N; next++) {
        if (!(mask & (1 << next))) { // ถ้ายังไม่ไปเมืองนี้
            // ไปเมือง next ต่อจากเมือง last
            long long cost = solve(mask | (1 << next), next, graph, memo) + graph[last][next];

            // ถ้าค่า cost ไม่ใช่ -INF แสดงว่าเส้นทางนี้เป็นไปได้
            if (cost != -INF) {
                best = max(best, cost);
            }
        }
    }

    return memo[mask][last] = best;
}

int main() {
    cin >> N;

    vector<vector<int>> graph(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    vector<vector<long long>> memo(1 << N, vector<long long>(N, -1));

    long long ans = solve(1, 0, graph, memo);

    cout << ans << endl;
}