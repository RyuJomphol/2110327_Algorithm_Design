#include <iostream>
#include <vector>

using namespace std;

void fwht(vector<int>& arr, int start , int len) {
    if(len == 1) return;

    int half = len / 2;

    for(int i = 0; i < half; i++) {
        int u = arr[start + i];
        int v = arr[start + half + i];

        arr[start + i] = u + v;
        arr[start + half + i] = u - v; 
    }
    fwht(arr, start, half);
    fwht(arr, start + half, half);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    fwht(v, 0, n);

    for (int i = 0 ; i < n ; i++) {
        cout << v[i] << " ";
    }
}