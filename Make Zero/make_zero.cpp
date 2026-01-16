#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long x;
    cin >> x;

    if (x == 0) {
        cout << 0 << endl;
        return 0;
    }

    int min_ops = 24; // ค่าสูงสุดที่เป็นไปได้คือคูณ 2 ให้ครบ 24 ครั้ง
    const int MOD_VAL = 16777216; // 2^24

    // j คือจำนวนครั้งที่จะกด Operation 2 (คูณ 2)
    for (int j = 0; j <= 24; j++) {
        // เป้าหมายคือ (x + i) * 2^j ต้องหารด้วย 2^24 ลงตัว
        // นั่นคือ (x + i) ต้องหารด้วย 2^(24-j) ลงตัว
        int divisor = 1 << (24 - j); 
        
        // หาว่าต้องบวก i อีกเท่าไหร่เพื่อให้ x กลายเป็นพหุคูณของ divisor
        int remainder = x % divisor;
        int i = (remainder == 0) ? 0 : (divisor - remainder);

        // จำนวนครั้งรวมคือ i (บวก) + j (คูณ)
        min_ops = min(min_ops, i + j);
    }

    cout << min_ops << endl;
    return 0;
}