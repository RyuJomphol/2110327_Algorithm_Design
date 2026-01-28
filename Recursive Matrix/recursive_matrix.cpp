#include <iostream>
#include <vector>

using namespace std;

void recur(vector<vector<int>> &v, int a, int b, int top, int bottom, int left, int right) {
    if (a == 0) {
        v[top][left] = b;
        return;
    }

    int mid_r = (top + bottom) / 2;
    int mid_c = (left + right) / 2;

    recur(v, a - 1, b, top, mid_r, left, mid_c);

    recur(v, a - 1, b - 1, top, mid_r, mid_c, right);

    recur(v, a - 1, b + 1, mid_r, bottom, left, mid_c);

    recur(v, a - 1, b, mid_r, bottom, mid_c, right);
}

int main() {
    int a, b;
    cin >> a >> b;

    int n = 1 << a; 
    vector<vector<int>> v(n, vector<int>(n));

    recur(v, a, b, 0, n, 0, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}