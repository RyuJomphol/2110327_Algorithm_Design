#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct virus {
    bool is_divoc;
    int count_one;
};

virus test_divoc(vector<int> gene , int start , int end , int k) {
    if (k == 0) {
        return {true, gene[start]};
    }

    int mid = (start + end) / 2;
    virus left = test_divoc(gene, start, mid, k - 1);
    virus right = test_divoc(gene, mid + 1, end, k - 1);

    bool current_is_divoc = left.is_divoc && right.is_divoc && (abs(left.count_one - right.count_one) <= 1);

    return {current_is_divoc, left.count_one + right.count_one};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n,k;
    cin >> n >> k;
    int virus_length = pow(2, k);

    for (int i = 0; i < n; i++) {
        vector<int> gene(virus_length);
        for (int j = 0; j < virus_length; j++) {
            cin >> gene[j];
        }

        virus final_result = test_divoc(gene , 0, virus_length - 1, k);

        if (final_result.is_divoc) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
        
    }
}
