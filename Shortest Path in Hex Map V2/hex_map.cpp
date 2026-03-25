#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int grid[305][305];
int dista[305][305];

int dr_odd[] = {0, 0, -1, -1, 1, 1};
int dc_odd[] = {-1, 1, 0, 1, 0, 1};
int dr_even[] = {0, 0, -1, -1, 1, 1};
int dc_even[] = {-1, 1, -1, 0, -1, 0};

int main() {
    int R, C;
    cin >> R >> C;
    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    for (int i = 1 ; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> grid[i][j];
            dista[i][j] = INF;
        }
    }

    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<>
    > pq;

    dista[a1][b1] = grid[a1][b1];
    pq.push({dista[a1][b1], a1, b1});

    while(!pq.empty()) {
        auto [cost, r, c] = pq.top();
        pq.pop();

        if (cost > dista[r][c]) continue;

        if (r == a2 && c == b2) {
            cout << cost;
            return 0;
        }

        for (int k = 0; k < 6; k++) {
            int nr, nc;
            if (r % 2 == 1) { //odd
                nr = r + dr_odd[k];
                nc = c + dc_odd[k]; 
            } 
            else { //even
                nr = r + dr_even[k];
                nc = c + dc_even[k];
            }

            if (nr < 1 || nr > R || nc < 1 || nc > C) continue;

            int newCost = cost + grid[nr][nc];

            if (newCost < dista[nr][nc]) {
                dista[nr][nc] = newCost;
                pq.push({newCost, nr, nc});
            }
        }
    }

    cout << dista[a2][b2];
 }