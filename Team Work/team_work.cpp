#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<int> task(M);
    for (int i = 0; i < M; i++) {
        cin >> task[i];
    }

    sort(task.begin(), task.end());

    long long total_sum = 0;
    long long multiplier = 1;
    int count = 0;

    for (int i = M - 1; i >= 0; i--) {
        total_sum += (long long)task[i] * multiplier;
        count++;
        
        if (count == N) {
            multiplier++;
            count = 0;
        }
    }

    double averageTime = (double)total_sum / M;

    cout << fixed << setprecision(3) << averageTime << endl;
}