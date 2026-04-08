#include <iostream>
#include <string>
#include <vector>

using namespace std;

string S;
long long total_ans = 0;

// ฟังก์ชันคืนค่าจำนวนเลข 0 ในช่วง [l, r]
int solve(int l, int r) {
    if (l == r) {
        return (S[l] == '0');
    }

    int m = (l + r) / 2;
    int zL = solve(l, m);      // จำนวน 0 ฝั่งซ้าย
    int zR = solve(m + 1, r);  // จำนวน 0 ฝั่งขวา
    
    int lenL = (m - l + 1);
    int lenR = (r - (m + 1) + 1);
    int oL = lenL - zL;        // จำนวน 1 ฝั่งซ้าย
    int oR = lenR - zR;        // จำนวน 1 ฝั่งขวา

    // คำนวณจำนวนครั้งของบรรทัด 11 และ 14 ตามตรรกะ Binary Merge
    if (oL == 0) {
        total_ans += (zR + oR); // ฝั่งซ้ายหมดเร็ว บรรทัด 14 ทำงานเท่ากับจำนวนที่เหลือในขวา
    } else if (oR == 0) {
        total_ans += oL;        // ฝั่งขวาหมดเร็ว บรรทัด 11 ทำงานเท่ากับจำนวน 1 ที่เหลือในซ้าย
    } else {
        total_ans += oR;        // ปกติฝั่งซ้ายจะดึง 1 จนหมดก่อน บรรทัด 14 จึงทำงานเท่ากับ 1 ในขวา
    }

    return zL + zR; // ส่งจำนวน 0 รวมกลับขึ้นไป
}

int main() {
    // ต้องใส่ตามคำแนะนำในโจทย์เพื่อความเร็ว [cite: 73]
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int N;
    if (!(cin >> N)) return 0;
    cin >> S;

    solve(0, N - 1);
    cout << total_ans << endl;

    return 0;
}