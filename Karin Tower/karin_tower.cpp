#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ใช้ค่า INF ที่มีขนาดใหญ่พอ แต่ไม่ทำให้เกิด Overflow เมื่อนำไปบวกเพิ่ม
const long long INF = 1e18;

typedef vector<vector<long long>> Matrix;

// ฟังก์ชันสำหรับคูณเมทริกซ์แบบ Min-Plus
Matrix multiply(const Matrix& A, const Matrix& B, int K) {
    Matrix C(K, vector<long long>(K, INF));
    for (int i = 0; i < K; ++i) {
        for (int k = 0; k < K; ++k) {
            if (A[i][k] == INF) continue;
            for (int j = 0; j < K; ++j) {
                if (B[k][j] == INF) continue;
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
    return C;
}

// ฟังก์ชันยกกำลังเมทริกซ์ (Matrix Exponentiation) $O(K^3 \log P)$
Matrix power(Matrix A, long long p, int K) {
    Matrix res(K, vector<long long>(K, INF));
    // เอกลักษณ์ของ Min-Plus คือ 0 ในแนวเส้นทแยงมุมหลัก และ INF ในช่องอื่น
    for (int i = 0; i < K; ++i) {
        res[i][i] = 0;
    }
    
    while (p > 0) {
        if (p % 2 == 1) res = multiply(res, A, K);
        A = multiply(A, A, K);
        p /= 2;
    }
    return res;
}

int main() {
    // เพิ่มประสิทธิภาพ I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    int K, P;
    
    if (!(cin >> N >> K >> P)) return 0;

    // อ่านค่าความยากของยามแต่ละห้อง
    vector<vector<long long>> cost(K, vector<long long>(5));
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> cost[i][j];
        }
    }

    // 1. หา Shortest Path บนชั้นเดียวกัน (Floyd-Warshall)
    Matrix dist(K, vector<long long>(K, INF));
    for (int i = 0; i < K; ++i) {
        dist[i][i] = 0;
        int left_room = (i - 1 + K) % K;
        int right_room = (i + 1) % K;
        dist[i][left_room] = min(dist[i][left_room], cost[i][0]);
        dist[i][right_room] = min(dist[i][right_room], cost[i][1]);
    }

    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < K; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 2. สร้าง Transition Matrix M สำหรับการเปลี่ยนชั้น
    Matrix M(K, vector<long long>(K, INF));
    for (int i = 0; i < K; ++i) {
        for (int x = 0; x < K; ++x) {
            if (dist[i][x] == INF) continue;
            
            int up_left = (x - 1 + K) % K;
            int up_mid = x;
            int up_right = (x + 1) % K;

            // อัปเดตค่าใช้จ่ายในการเดินไปห้อง x แล้วขึ้นข้างบน
            M[i][up_left]  = min(M[i][up_left],  dist[i][x] + cost[x][2]);
            M[i][up_mid]   = min(M[i][up_mid],   dist[i][x] + cost[x][3]);
            M[i][up_right] = min(M[i][up_right], dist[i][x] + cost[x][4]);
        }
    }

    // 3. หาค่าใช้จ่ายผ่านชั้นต่างๆ ด้วย Matrix Exponentiation
    // ถ้า N=1 แสดงว่าไม่ได้ขึ้นชั้นใหม่เลย (N-1 = 0) จะได้ Identity Matrix
    Matrix R = power(M, N - 1, K);

    // 4. หาคำตอบที่น้อยที่สุด (เดินมาถึงชั้น N-1 ที่ห้อง j แล้วเดินต่อหาห้อง P)
    long long final_ans = INF;
    for (int j = 0; j < K; ++j) {
        if (R[0][j] != INF && dist[j][P] != INF) {
            final_ans = min(final_ans, R[0][j] + dist[j][P]);
        }
    }

    cout << final_ans << "\n";

    return 0;
}