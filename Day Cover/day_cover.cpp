#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int student_min = 20; // 1 <= n <= 1000 & 1 <= m <=20
int n,m;
vector<vector<int>> students;
vector<int> dayCoveredCount;
int currentDaysCovered = 0;

void combi(int studentIdx, int num_student_use) {
    if (num_student_use >= student_min) {
        return;
    }
    
    if (currentDaysCovered == n) {
        student_min = min(student_min, num_student_use);
        return;
    }

    if (studentIdx == m) {
        return;
    }

    //(Update State)
    for (int day : students[studentIdx]) {
        if (dayCoveredCount[day] == 0) {
            currentDaysCovered++;
        }
        dayCoveredCount[day]++;
    }

    combi(studentIdx + 1 , num_student_use + 1);

    //(Undo State)
    for (int day : students[studentIdx]) {
        dayCoveredCount[day]--;
        if (dayCoveredCount[day] == 0) {
            currentDaysCovered--;
        }
    }

    combi(studentIdx + 1, num_student_use);
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cin >> n >> m;
    students.resize(m);
    dayCoveredCount.resize(n + 1, 0);

    for (int i = 0 ; i < m ; i++) {
        int k;
        cin >> k;
        students[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> students[i][j];
        }
    }
    combi(0,0);

    cout << student_min << endl;
}