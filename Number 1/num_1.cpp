#include <iostream>

using namespace std;

int get_length(int n) {
    if (n <= 1) return 1;
    int len = 1;
    while (n > 1) {
        n = n / 2;
        len = len * 2 + 1;
    }
    return len;
}

int count_ones(int n, int start, int end, int left, int right) {
    if (start > left || end < right || n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    int mid = start + (end - start) / 2;
    int res = 0;

    res += count_ones(n / 2, start, mid - 1, left, right);

    if (mid >= left && mid <= right) {
        res += (n % 2);
    }

    res += count_ones(n / 2, mid + 1, end, left, right);

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, r;
    cin >> n >> l >> r;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    int total_length = get_length(n);

    cout << count_ones(n, 1, total_length, l, r) << endl;
}