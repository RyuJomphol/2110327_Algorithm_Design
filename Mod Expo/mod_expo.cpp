#include <iostream>
#include <vector>

using namespace std;

long long power(long long x, long long n, long long k) {
    long long res = 1;
    x = x % k;

    while (n > 0) {
        if (n % 2 == 1) {
            res = (res * x) % k;
        }
        x = (x * x) % k;
        n = n / 2;
    }
    return res;
};

int main() {
    long long X,M,K;
    cin >> X >> M >> K;
    long long result = power(X,M,K);
    cout << result << endl;
}