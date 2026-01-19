#include <iostream>
#include <vector>

using namespace std;

int N,M,num1,num2;
vector<int> v;

int find_num(int k) {
    int low = -1;
    int high = N - 1;
    while (low < high) {
        int middle = (low + high + 1) / 2;
        if (v[middle] <= k) {
            low = middle;
        }
        else {
            high = middle - 1;
        }
    }
    return high;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    v.resize(N);
    for(int i = 0 ; i < N ; i++) {
        cin >> num1;
        v[i] = num1;
    }
    while(M--) {
        cin >> num2;
        int idx = find_num(num2);
        cout << idx << endl; 
    }
}