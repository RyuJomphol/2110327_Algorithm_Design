#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool isDivoc(vector<int> v , int k) {
    if (k == 1) {
        return (v.size() == 2 && v[0] == 0 && v[1] == 1);
    }

    int n = v.size();
    int mid = n / 2;

    vector<int> left(v.begin(), v.begin() + mid);
    vector<int> right(v.begin() + mid, v.end());

    if (!isDivoc(right, k - 1)) {
        return false;
    }

    bool leftNormal = isDivoc(left, k - 1);
    
    reverse(left.begin(), left.end());
    bool leftReversed = isDivoc(left, k - 1);

    return leftNormal || leftReversed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,k;
    cin >> n >> k;
    int length = pow(2, k);

    for (int i = 0; i < n; i++) {
        vector<int> sequence(length);
        for (int j = 0; j < length; j++) {
            cin >> sequence[j];
        }

        if (isDivoc(sequence, k)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}