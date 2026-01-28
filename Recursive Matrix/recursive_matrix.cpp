#include <iostream>
#include <cmath>

using namespace std;

int get_value(int a, int b, int r, int c) {
    if (a == 0) {
        return b;
    }

    int half = pow(2, a-1);

    if (r < half && c < half) {
        return get_value(a - 1, b, r, c);
    }
    else if (r < half && c >= half) {
        return get_value(a - 1, b - 1, r, c - half);
    }
    else if (r >= half && c < half) {
        return get_value(a - 1, b + 1, r - half, c);
    }
    else {
        return get_value(a - 1, b, r - half, c - half);
    }
}

int main() {
    int a, b;
    cin >> a >> b;
    int n = pow(2, a);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n ; j++) {
            cout << get_value(a,b,i,j) << (j == n - 1 ? "" : " ");
        }
        cout << "\n";
    }
}