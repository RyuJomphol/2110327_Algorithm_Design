#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L;
    cin >> N >> L;

    vector<int> drainages(N);
    for (int i = 0; i < N; i++) {
        cin >> drainages[i];
    }

    sort(drainages.begin(), drainages.end());

    int count = 0;
    int cover_until = -1;

    for (int i = 0; i < N; i++) {
        if (drainages[i] > cover_until) {
            count++;
            cover_until = drainages[i] + L - 1;
        }
    }

    cout << count << endl;
}