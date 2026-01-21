#include <iostream>
#include <vector>

using namespace std;

struct Matrix {
    long long mat[2][2];
};

Matrix multiply(Matrix A, Matrix B, int k) {
    Matrix C;
    for(int i = 0 ; i < 2 ; i++) { 
        for(int j = 0 ; j < 2 ; j++) {
            C.mat[i][j] = 0;
            for (int l = 0; l < 2; l++) {
                C.mat[i][j] = (C.mat[i][j] + (A.mat[i][l] * B.mat[l][j])) % k;
            }
        }  
    }
    return C;
};

Matrix power(Matrix A, int n, int k) {
    Matrix res;
    res.mat[0][0] = 1; res.mat[0][1] = 0;
    res.mat[1][0] = 0; res.mat[1][1] = 1;

    A.mat[0][0] %= k; A.mat[0][1] %= k;
    A.mat[1][0] %= k; A.mat[1][1] %= k;

    while (n > 0) {
        if (n % 2 == 1) {
            res = multiply(res, A, k);
        }
        A = multiply(A, A, k);
        n /= 2;
    }
    return res;
};

int main () {
    int n,k;
    cin >> n >> k;

    Matrix A;
    cin >> A.mat[0][0] >> A.mat[0][1] >> A.mat[1][0] >> A.mat[1][1];

    Matrix result = power(A,n,k);
    cout << result.mat[0][0] << " " << result.mat[0][1] << " " << result.mat[1][0] << " " << result.mat[1][1];
}