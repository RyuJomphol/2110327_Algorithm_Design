#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N);

    for (int i = 0; i < N; i++) cin >> a[i];

    int totalSum = a[0];
    int maxEnding = a[0];
    int maxNormal = a[0];
    int minEnding = a[0]; 
    int minSub = a[0];

    for (int i = 1; i < N; i++) {
        totalSum += a[i];

        maxEnding = max(a[i], maxEnding + a[i]);
        maxNormal = max(maxNormal, maxEnding);

        minEnding = min(a[i], minEnding + a[i]);
        minSub = min(minSub, minEnding);
    }

    if (maxNormal < 0) {
        cout << maxNormal;
    } else {
        cout << max(maxNormal, totalSum - minSub);
    }
}