#include <iostream>
#include <vector>

using namespace std;

long long N;
long long MOD = 100000007;

struct Matrix {
    int mat[3][3];
    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = 0;
            }
        }
    }
};

Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                result.mat[i][j] = (result.mat[i][j] + (long long)A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return result;
}

Matrix matrix_pow(Matrix base, long long exp) {
    Matrix result;
    for (int i = 0; i < 3; i++) {
        result.mat[i][i] = 1;
    }
    base.mat[0][0] %= MOD;
    base.mat[0][1] %= MOD;
    base.mat[0][2] %= MOD;
    base.mat[1][0] %= MOD;
    base.mat[1][1] %= MOD;
    base.mat[1][2] %= MOD;
    base.mat[2][0] %= MOD;
    base.mat[2][1] %= MOD;
    base.mat[2][2] %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp /= 2;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    Matrix T;
    T.mat[0][0] = 1; T.mat[0][1] = 0; T.mat[0][2] = 1;
    T.mat[1][0] = 1; T.mat[1][1] = 1; T.mat[1][2] = 0;
    T.mat[2][0] = 0; T.mat[2][1] = 1; T.mat[2][2] = 0;

    T = matrix_pow(T, N - 1);

    long long countState0 = (T.mat[0][0] + T.mat[0][1]) % MOD;
    long long countState1 = (T.mat[1][0] + T.mat[1][1]) % MOD;
    long long countState2 = (T.mat[2][0] + T.mat[2][1]) % MOD;
    long long total = countState0 + countState1 + countState2;
    total %= MOD;
    cout << total << "\n";
}