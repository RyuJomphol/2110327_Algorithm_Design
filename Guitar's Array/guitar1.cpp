#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool all_same (vector<int> dadada, int start, int end, int rank) {
    for (int i = start; i <= end; i++) {
        if (dadada[i] != rank) return false;
    }
    return true;
}

bool is_pung (vector<int> dadada, int start, int end, int rank) {
    if (start == end) {
        return (dadada[start] == rank);
    }

    int mid = (start + end) / 2;
    return (all_same(dadada, start, mid, rank) && is_pung(dadada, mid + 1, end, rank + 1) || is_pung(dadada, start, mid, rank + 1) && all_same(dadada, mid + 1, end, rank));
}


int main() {
    int T;
    cin >> T;
    int full_size = pow(2,T);
    vector<int> arrayja(full_size);
    
    for (int i = 0; i < T ; i++) {
        int k, x;
        cin >> k >> x;
        int full_size = pow(2,k);
        vector<int> arrayja(full_size);
        for (int j = 0; j < full_size; j++) {
            cin >> arrayja[j];
        }
        
        if (is_pung(arrayja, 0, full_size - 1, x)) {
           cout << "YES" << "\n";
        }
        else {
            cout << "NO" << "\n";
        }
    }
}