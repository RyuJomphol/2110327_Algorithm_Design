#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// โครงสร้างสำหรับเก็บพิกัดจุด
struct Point {
    long long x, y;
};

// ฟังก์ชันเปรียบเทียบเพื่อเรียงตามแกน X
bool compareX(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// ฟังก์ชันเปรียบเทียบเพื่อเรียงตามแกน Y
bool compareY(const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

// ฟังก์ชันคำนวณระยะทางยกกำลังสอง
long long distSquared(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// ฟังก์ชันหลักแบบ Divide and Conquer
long long closestPair(vector<Point>& points, int left, int right) {
    // Base case: ถ้ามีจุดเหลือน้อยกว่าหรือเท่ากับ 3 จุด ให้ใช้ Brute Force
    if (right - left <= 3) {
        long long minDist = -1;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                long long d = distSquared(points[i], points[j]);
                if (minDist == -1 || d < minDist) {
                    minDist = d;
                }
            }
        }
        return minDist;
    }

    // Divide: แบ่งครึ่ง
    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    // Conquer: หาค่าต่ำสุดจากฝั่งซ้ายและขวา
    long long dl = closestPair(points, left, mid);
    long long dr = closestPair(points, mid, right);
    long long d = min(dl, dr);

    // Combine: ตรวจสอบจุดที่อยู่ระหว่างรอยต่อ
    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        // ระยะห่างแกน X ต้องน้อยกว่า sqrt(d) 
        // เขียนในรูปยกกำลังสองเพื่อเลี่ยง floating point
        if ((points[i].x - midPoint.x) * (points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    // เรียงจุดใน strip ตามแกน Y
    sort(strip.begin(), strip.end(), compareY);

    // เปรียบเทียบจุดใน strip
    int size = strip.size();
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, distSquared(strip[i], strip[j]));
        }
    }

    return d;
}

int main() {
    // ปรับความเร็ว I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }

        // เรียงลำดับตามแกน X ก่อนเริ่มทำ Divide and Conquer
        sort(points.begin(), points.end(), compareX);

        cout << closestPair(points, 0, n) << "\n";
    }

    return 0;
}