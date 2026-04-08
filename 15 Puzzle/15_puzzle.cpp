#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int board[4][4];
int goal_x[16], goal_y[16];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int limit;
bool solved;
int next_limit;

int get_heuristic(int b[4][4]) {
    int distance = 0;
    for (int i = 0 ; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int val = b[i][j];
            if (val != 0) {
                distance += abs(i - goal_x[val]) + abs(j - goal_y[val]);
            }
        }
    }
    return distance;
}

void dfs(int depth, int last_move, int empty_r, int empty_c) {
    int h = get_heuristic(board);
    int f = depth + h;
    if (f > limit) {
        next_limit = min(next_limit, f);
        return;
    }

    if (h == 0) {
        solved = true;
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (last_move != -1 && (i ^ 1) == last_move) continue;
        int nr = empty_r + dx[i];
        int nc = empty_c + dy[i];

        if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
            swap(board[empty_r][empty_c], board[nr][nc]);
            dfs(depth + 1, i, nr, nc);
            if (solved) return;
            swap(board[empty_r][empty_c], board[nr][nc]);
        }
    }
}

int main() {
    int start_r, start_c;
    for (int i = 0; i < 15; i++) {
        goal_x[i + 1] = i / 4;
        goal_y[i + 1] = i % 4;
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> board[i][j];
            if (board[i][j] == 0) {
                start_r = i;
                start_c = j;
            }
        }
    }

    limit = get_heuristic(board);
    solved = false;

    while (!solved && limit < 100) {
        next_limit = 1e9;
        dfs(0, -1, start_r, start_c);
        if (!solved) {
            limit = next_limit;
        }
    }
}