#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int countDays(const vector<int>& heights, int K) {
    int days = 0;
    int currenntPos = 0; // Start at the base of the mountain
    int n = heights.size() - 1; // Exclude the dummy height

    while (currenntPos < heights[n]) {
        auto it = upper_bound(heights.begin(), heights.end(), currenntPos + K);
        it--;

        int nextPos = *it;
        currenntPos = nextPos;
        days++;
    }
    return days;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, D;
    cin >> N >> D;

    vector<int> heights;
    heights.push_back(0); // Add a dummy height for the base of the mountain
    int maxGap = 0;

    for (int i = 0; i < N; i++) {
        int h;
        cin >> h;
        heights.push_back(h);
        maxGap = max(maxGap, heights[i+1] - heights[i]);
    }

    int low = maxGap; // The minimum possible D is the maximum gap between consecutive heights
    int high = 1000000000; // A large number to ensure we cover all possibilities
    int ansK = high;
    int ansDays = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int d = countDays(heights, mid);

        if (d <= D) {
            ansK = mid;
            ansDays = d;
            high = mid - 1; // Try to find a smaller K
        } else {
            low = mid + 1; // Need a larger K
        }
    }

    cout << ansK << " " << ansDays << endl;
}