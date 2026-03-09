#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    if (k == 2) {
        // กรณี k=2: สร้าง Subset ขนาด n และส่วนเติมเต็ม
        vector<int> current;
        generate_k2(n, 1, current, 2 * n);
    } else if (n == 2) {
        // กรณี n=2: ใช้ Circle Method (Round-Robin)
        solve_n2(k);
    } else {
        // กรณีทั่วไป: ยังไม่มีวิธีที่มีประสิทธิภาพสูง
        cout << "ยังไม่มีวิธีที่มีประสิทธิภาพสูงสำหรับกรณีนี้\n";
    }

    return 0;
}