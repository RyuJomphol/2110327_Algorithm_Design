//This sol is P 50 T 50

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int N,Q;

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    map<int,int> group;
    cin >> N >> Q;
    for (int i = 0 ; i < N ; i++) {
        int X,C;
        cin >> X >> C;
        group[X] += C;
    }

    vector<pair<int,int>> array;
    for (auto x : group) {
        array.push_back(make_pair(x.first,x.second));
    }

    sort(array.begin(),array.end());

    for (int i = 0 ; i < Q ; i++) {
        int input;
        cin >> input;
        for(int j = 0 ; j < array.size() ; j++) {
            if (input - array[j].second > 0) {
                input -= array[j].second;
            }
            else {
                cout << array[j].first << endl;
                break;
            }
        }
    }
}