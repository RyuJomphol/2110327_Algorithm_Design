#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> P(N, vector<int>(M));

    int val;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> val;
            
            int top = (i > 0) ? P[i-1][j] : 0;
            int left = (j > 0) ? P[i][j-1] : 0;
            int diag = (i > 0 && j > 0) ? P[i-1][j-1] : 0;
            P[i][j] = val + top + left - diag;
        }
    }
    int r1, c1, r2, c2;
    for (int k = 0; k < K; k++) {
        cin >> r1 >> c1 >> r2 >> c2;
    
        int total = P[r2][c2];
        int top_sub = (r1 > 0) ? P[r1-1][c2] : 0;
        int left_sub = (c1 > 0) ? P[r2][c1-1] : 0;
        int add_back = (r1 > 0 && c1 > 0) ? P[r1-1][c1-1] : 0;
        cout << total - top_sub - left_sub + add_back << "\n";
    }
}