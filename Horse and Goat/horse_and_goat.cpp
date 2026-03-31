#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 3505;
const int INF = 1e9;

char grid[MAX][MAX];
int dist[MAX][MAX];

bool row_launched[MAX];
bool col_launched[MAX]; // Track if we've launched a rocket in this row/column

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    int start_r = -1, start_c = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                start_r = i;
                start_c = j;
            }
            dist[i][j] = INF;
        }
    }

    queue<pair<int, int>> q;
    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (grid[r][c] == 'T') {
            cout << dist[r][c] << "\n";
            return 0;
        }

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (grid[nr][nc] != 'X' && dist[nr][nc] == INF) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        if (grid[r][c] == '#') {
            if (!row_launched[r]) {
                row_launched[r] = true;
                for (int nc = 0; nc < M; nc++) {
                    if (grid[r][nc] != 'X' && dist[r][nc] == INF) {
                        dist[r][nc] = dist[r][c] + 1;
                        q.push({r, nc});
                    }
                }
            }
            if (!col_launched[c]) {
                col_launched[c] = true;
                for (int nr = 0; nr < N; nr++) {
                    if (grid[nr][c] != 'X' && dist[nr][c] == INF) {
                        dist[nr][c] = dist[r][c] + 1;
                        q.push({nr, c});
                    }
                }
            }
        }
    }
}