#include <iostream>
#include <string>

using namespace std;

// ประกาศตัวแปร Global เพื่อให้ฟังก์ชัน recursion เรียกใช้ได้ง่าย
int N, W, B;
string current_path = "";

// ฟังก์ชัน Recursive สำหรับค้นหาคำสั่ง
// step: วินาทีปัจจุบัน (เริ่มจาก 0 ถึง N)
// current_h: ความสูงของยานในปัจจุบัน
void solve(int step, int current_h) {
    // Base Case: ถ้าเลือกคำสั่งครบ N วินาทีแล้ว
    if (step == N) {
        cout << current_path << "\n";
        return;
    }

    // เพื่อให้เรียงตามพจนานุกรม เราจะลองเดินตามลำดับ D -> S -> U

    // 1. ลองเดินลง 'D'
    if (current_h - 1 >= 1) { // ตรวจสอบว่าไม่ชนพื้น
        current_path.push_back('D');
        solve(step + 1, current_h - 1);
        current_path.pop_back(); // Backtrack เอาออกเพื่อลองทางอื่น
    }

    // 2. ลองอยู่ที่เดิม 'S'
    if (current_h >= 1 && current_h <= W) { // ตรวจสอบว่าปลอดภัย (จริงๆ ปลอดภัยอยู่แล้ว)
        current_path.push_back('S');
        solve(step + 1, current_h);
        current_path.pop_back(); // Backtrack
    }

    // 3. ลองเดินขึ้น 'U'
    if (current_h + 1 <= W) { // ตรวจสอบว่าไม่ชนเพดาน
        current_path.push_back('U');
        solve(step + 1, current_h + 1);
        current_path.pop_back(); // Backtrack
    }
}

int main() {
    // ใส่คำสั่งเพิ่มความเร็วในการ I/O ตามคำแนะนำของโจทย์
    ios::sync_with_stdio(false);
    cin.tie(0);

    // รับค่า N (จำนวนวินาที), W (ความสูงฉาก), B (ความสูงเริ่มต้น)
    if (cin >> N >> W >> B) {
        solve(0, B);
    }

    return 0;
}