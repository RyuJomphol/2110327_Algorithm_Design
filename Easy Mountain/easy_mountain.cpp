#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<long long> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    vector<long long> dp(N + 1, 0);
    
    // อาร์เรย์เก็บค่า dp สูงสุดสำหรับแต่ละค่า A[j] ที่เคยเจอมา
    // เนื่องจาก A[i] <= 100 เราจึงใช้อาร์เรย์ขนาด 105 ก็พอ
    vector<long long> max_val_for_A(105, -1);

    // ที่จุดเริ่มต้น (จุดที่ 1)
    max_val_for_A[A[1]] = 0; // dp[1] = 0

    for (int i = 2; i <= N; i++) {
        long long current_best = 0;
        
        // แทนที่จะวนลูป j ตั้งแต่ 1 ถึง i-1
        // เราวนลูปตามค่าความสูงที่เป็นไปได้คือ 1 ถึง 100 แทน!
        for (int v = 1; v <= 100; v++) {
            if (max_val_for_A[v] != -1) { // ถ้าเคยมีจุดก่อนหน้าที่มีความสูง v
                long long sum_val = v + A[i];
                long long cost = sum_val * sum_val * sum_val;
                
                current_best = max(current_best, max_val_for_A[v] + cost);
            }
        }
        
        dp[i] = current_best;
        
        // อัปเดตว่า ณ ความสูง A[i] นี้ ได้ค่า dp ที่ดีที่สุดเท่าไหร่
        max_val_for_A[A[i]] = max(max_val_for_A[A[i]], dp[i]);
    }

    cout << dp[N] << "\n";

    return 0;
}