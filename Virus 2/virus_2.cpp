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


        
    }
}
