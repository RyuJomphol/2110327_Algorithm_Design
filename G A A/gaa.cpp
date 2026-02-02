#include <iostream>
#include <vector>

using namespace std;

char find_char(int n, int k, int current_len) {
    if (k == 0) {
        if (n == 1) return 'g';
        return 'a';
    }

    int prev_len = (current_len - (k + 3)) / 2;

    if (n <= prev_len) {
        return find_char(n, k - 1, prev_len);
    }
    else if (n <= prev_len + (k + 3)) {
        if (n == prev_len + 1) return 'g';
        return 'a';
    }
    else {
        return find_char(n - prev_len - (k + 3), k - 1, prev_len);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    int len = 3;
    int k = 0;
    while (len < n) {
        k++;
        len = 2 * len + (k + 3);
    }

    cout << find_char(n, k, len) << endl;
}