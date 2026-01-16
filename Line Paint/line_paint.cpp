#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start, end;
    bool operator<(const Interval& other) const {
        if (start != other.start)
            return start < other.start;
        return end < other.end;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Interval> intervals(n);
    vector<int> result;
    for (int i = 0 ; i < n ; i++) {
        cin >> intervals[i].start >> intervals[i].end;
    }

    sort(intervals.begin(), intervals.end());

    int current_start = intervals[0].start;
    int current_end = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= current_end + 1) {
            current_end = max(current_end, intervals[i].end);
        } else {
            cout << current_start << " " << current_end << " ";
            
            current_start = intervals[i].start;
            current_end = intervals[i].end;
        }
    }
    
    cout << current_start << " " << current_end;

    return 0;
}