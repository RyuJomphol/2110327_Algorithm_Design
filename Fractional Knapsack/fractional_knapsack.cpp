#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    double value;
    double weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double W;
    int N;
    
    cin >> W >> N;
    vector<Item> items(N);
    for (int i = 0; i < N; i++) {
        cin >> items[i].value;
    }
    for (int i = 0; i < N; i++) {
        cin >> items[i].weight;
    }
    for (int i = 0; i < N; i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    for (int i = 0; i < N; i++) {
        if (currentWeight + items[i].weight <= W) {
            totalValue += items[i].value;
            currentWeight += items[i].weight;
        } else {
            double remainingWeight = W - currentWeight;
            totalValue += items[i].ratio * remainingWeight;
            break;
        }
    }

    cout << fixed << setprecision(4) << totalValue << endl;
}