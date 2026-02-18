#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_val(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    int global_max = -1000000000;

    auto process_diagonal = [&](int start_row, int start_col) {
        int current_max = -1000000000;
        int row = start_row;
        int col = start_col;

        while (row < n && col < n)
        {
            int value = A[row][col];
            if (current_max < 0) {
                current_max = value;
            }
            else {
                current_max = max_val(current_max + value, value);
            }

            if (current_max > global_max) {
                global_max = current_max;
            }
            row++;
            col++;
        }
    };

    for (int c = 0; c < n; c++) {
        process_diagonal(0, c);
    }

    for (int r = 1; r < n; r++) {
        process_diagonal(r, 0);
    }

    cout << global_max << "\n";
}