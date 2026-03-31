#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// ใช้เก็บข้อมูลคนที่เดินในพิกัด Y
vector<long long> Y;
// ใช้ Memoization เพื่อไม่ให้คำนวณช่วง [b, c] ซ้ำ
map<pair<long long, long long>, long long> memo;

// ฟังก์ชันหาจำนวนคนที่เดินในช่วง [b, c]
long long count_people(long long b, long long c) {
    auto it1 = lower_bound(Y.begin(), Y.end(), b);
    auto it2 = upper_bound(Y.begin(), Y.end(), c);
    return distance(it1, it2);
}

// ฟังก์ชัน DP แบบ Recursive
long long solve(long long b, long long c) {
    long long L = c - b + 1;
    long long current_score = count_people(b, c);
    
    // ถ้าไม่มีคนเดินในช่วงนี้เลย ก็ไม่ต้องทำต่อ ได้คะแนน 0
    if (current_score == 0) return 0;
    
    // ถ้าความยาวช่วงน้อยกว่า 3 หุ่นยนต์จะหยุดทำงาน ได้แค่คะแนนในรอบนี้
    if (L < 3) return current_score;
    
    // ตรวจสอบว่าเคยคำนวณช่วงนี้ไปหรือยัง
    pair<long long, long long> state = {b, c};
    if (memo.count(state)) return memo[state];
    
    // คำนวณขนาดของช่วงย่อย
    long long u = L / 3;
    long long v = (L + 1) / 3;
    
    // พิกัดของ 3 ช่วงย่อย
    long long b1 = b, c1 = b + u - 1;
    long long b2 = b + u, c2 = b + u + v - 1;
    long long b3 = b + u + v, c3 = c;
    
    // คำนวณผลลัพธ์ของแต่ละช่วงย่อย
    long long s1 = solve(b1, c1);
    long long s2 = solve(b2, c2);
    long long s3 = solve(b3, c3);
    
    // เลือก 2 ช่วงจาก 3 ช่วงที่ให้ผลรวมมากที่สุด
    long long max_sub = max({s1 + s2, s1 + s3, s2 + s3});
    
    return memo[state] = current_score + max_sub;
}

int main() {
    // ปรับความเร็ว I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long W;
    int N;
    if (!(cin >> W >> N)) return 0;
    
    Y.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> Y[i];
    }
    
    // จัดเรียงพิกัดเพื่อให้ใช้ Binary Search ได้
    sort(Y.begin(), Y.end());
    
    // เริ่มทำงานจากช่วงเริ่มต้น [1, W]
    cout << solve(1, W) << "\n";
    
    return 0;
}