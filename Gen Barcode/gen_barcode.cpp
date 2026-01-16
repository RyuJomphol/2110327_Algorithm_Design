#include <iostream>
#include <vector>

using namespace std;

vector<string> all_nums;

void recursive(string num , int n , int k , int one) {

    if (n == 0) {
        if (one == k) all_nums.push_back(num);
        return;
    }

    recursive(num + "0" , n - 1 , k , one);
    recursive(num + "1" , n - 1 , k , one + 1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int k , n;
    cin >> k >> n;
    recursive("" , n , k , 0);
    for (auto num : all_nums) {
        cout << num << "\n";
    }
}