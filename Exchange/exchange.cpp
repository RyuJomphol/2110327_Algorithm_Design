#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K;
    cin >> K;
    while (K--) {
        int N;
        cin >> N;

        // vector to store the exchange rates
        vector<vector<double>> exchange(N, vector<double>(N));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> exchange[i][j];
            }
        }

        bool found = false;
        // Floyd-Warshall
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (exchange[i][k] * exchange[k][j] > exchange[i][j]) {
                        exchange[i][j] = exchange[i][k] * exchange[k][j];
                    }
                }
            }

            // ตรวจสอบเงื่อนไขหลังจบแต่ละรอบของ k
            for (int i = 0; i < N; i++) {
                if (exchange[i][i] > 1.0000000001) {
                    found = true;
                    break;
                }
            }
            if (found) break; // ออกจาก loop k ถ้าเจอแล้ว
        }

        if (found) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

    }
    
}