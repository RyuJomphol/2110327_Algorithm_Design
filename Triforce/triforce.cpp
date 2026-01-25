#include <iostream>
#include <vector>

using namespace std;

int grid[256][256];

bool isAllZero(int r, int c, int s) {
    for (int i = r; i < r + s ; i++) {
        for (int j = c; j < c + s ; j++) {
            if (grid[i][j] != 0) return false;
        }
    }
    return true;
}

int getTriforceType(int r, int c, int n) {
    if (n == 2) {
        if (grid[r + 1][c + 1] != 0) return 0;

        int v1 = grid[r][c];
        int v2 = grid[r][c + 1];
        int v3 = grid[r + 1][c];

        if (v1 == 0 || v2 == 0 || v3 == 0) return 0;

        if (v1 == v2 || v1 == v3) return v1;
        if (v2 == v3) return v2;

        return 0;
    }

    int m = n / 2;

    if(!isAllZero(r + m, c + m, m)) return 0;

    int typeP = getTriforceType(r, c, m);
    int typeQ = getTriforceType(r, c + m, m);
    int typeR = getTriforceType(r + m, c, m);

    if (typeP == 0 || typeQ == 0 || typeR == 0) return 0;

    if (typeP == typeQ || typeP == typeR) return typeP;
    if (typeQ == typeR) return typeQ;

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int test = 0 ; test < 3 ; test++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        cout << getTriforceType(0, 0, n) << "\n";
    }
}