 #include <iostream>
 #include <vector>

 using namespace std;

 vector<string> all_word;

 void recursive(string word , int n , int a , int b , int c) {
     if (n == 0) {
         all_word.push_back(word);
         return;
     }
     else {
         if(a > 0) recursive(word + "A", n - 1 , a - 1 , b , c);
         if(b > 0) recursive(word + "B", n - 1 , a , b - 1 , c);
         if(c > 0) recursive(word + "C", n - 1 , a , b , c - 1);
     }
 }

 int main() {
     ios_base::sync_with_stdio(false); cin.tie(0);
     int N,i,j,k;
     cin >> N >> i >> j >> k;
     recursive("",N,i,j,k);
     cout << all_word.size() << "\n";
     for (auto x : all_word) {
         cout << x << "\n";
     } 
}