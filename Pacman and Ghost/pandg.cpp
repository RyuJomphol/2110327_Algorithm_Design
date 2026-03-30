#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Ghost {
    int t, r, c;
};

const int INF = 1e9;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K;
    cin >> K;
    while (K--) {
        int R, C, n, T, r, c;
        cin >> R >> C >> n >> T >> r >> c;

        vector<Ghost> ghosts(n);
        for (int i = 0; i < n ; i++) {
            cin >> ghosts[i].t >> ghosts[i].r >> ghosts[i].c;
        }

        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            cin >> grid[i];
        }

        vector<vector<int>> distPacman(R, vector<int>(C, INF));
        queue<pair<int, int>> qPacman;
        if (grid[r][c] != '#') {
            distPacman[r][c] = 0;
            qPacman.push({r, c});
        }

        while (!qPacman.empty()) {
            auto [x, y] = qPacman.front();
            qPacman.pop();

            for (int d = 0; d < 4; d++) {
                int nx = x + dr[d];
                int ny = y + dc[d];

                if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] != '#' && distPacman[nx][ny] == INF) {
                    distPacman[nx][ny] = distPacman[x][y] + 1;
                    qPacman.push({nx, ny});
                }
            }
        }

        vector<vector<int>> distGhost(R, vector<int>(C, INF));
        priority_queue<pair<int, pair<int, int>>,
                    vector<pair<int, pair<int, int>>>
                    , greater<pair<int, pair<int, int>>>> pqG;
        
        for (int i = 0; i < n; i++) {
            int gr = ghosts[i].r;
            int gc = ghosts[i].c;
            int gt = ghosts[i].t;
            if (gt < distGhost[gr][gc]) {
                distGhost[gr][gc] = gt;
                pqG.push({gt, {gr, gc}});
            }
        }

        while (!pqG.empty()) {
            auto [t, pos] = pqG.top();
            auto [x, y] = pos;
            pqG.pop();

            if (distGhost[x][y] < t) continue;

            for (int d = 0; d < 4; d++) {
                int nx = x + dr[d];
                int ny = y + dc[d];

                if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] != '#' && distGhost[nx][ny] > t + 1) {
                    distGhost[nx][ny] = t + 1;
                    pqG.push({t + 1, {nx, ny}});
                }
            }
        }

        bool canEscape = false;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (distPacman[i][j] <= T && distGhost[i][j] > T) {
                    canEscape = true;
                    break;
                }
            }
            if (canEscape) break;
        }
        cout << (canEscape ? "YES" : "NO") << "\n";
    }

}