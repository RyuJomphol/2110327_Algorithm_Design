#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n,k;
int call_function = 1;
vector<int> v;

void gen_unsort(int left , int right) {
    if (call_function >= k || right - left <= 1) {
        return;
    }

    call_function += 2;
    int middle = (left + right) / 2;
    
    swap(v[middle - 1] , v[middle]);

    gen_unsort(left , middle);
    gen_unsort(middle , right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    v.resize(n);
    
    if (k % 2 == 0 || k > 2*n-1) {
        cout << "-1" << endl;
        return 0;
    }

    for (int i = 0 ; i < n ; i++) {
        v[i] = i + 1;
    }

    gen_unsort(0, n);

    for (int i = 0 ; i < n ; i++) {
        cout << v[i] << " ";
    }
}