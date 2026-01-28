#include <iostream>
#include <algorithm>

using namespace std;

long long U, V, W, P;

long long solve(long long n, long long r, long long c) {
    if (n == 1) {
        if (r == 1 && c == 1) return U;
        if (r == 1 && c == 2) return V;
        if (r == 2 && c == 1) return W;
        if (r == 2 && c == 2) return P;
        return 0;
    }

    long long half = 1LL << (n - 1);

    if (r <= half && c <= half) {
        return solve(n - 1, r, c);
    } 
    else if (r <= half && c > half) {
        return solve(n - 1, c - half, r);
    } 
    else if (r > half && c <= half) {
        return -1 * solve(n - 1, r - half, c);
    } 
    else {
        return -1 * solve(n - 1, c - half, r - half);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    long long n, m;
    cin >> n >> m;

    cin >> U >> V >> W >> P;

    while(m--) {
        long long r, c;
        cin >> r >> c;
        cout << solve(n ,r ,c) << "\n";
    }
}