#include <bits/stdc++.h>

using namespace std 


int main() {
    int t;
    cin >> t;
    while (t--) {

        int a, b;
        cin >> a >> b;
        if (b < 2*a) {
            cout << (b/2)*3 << endl;
        } else {
            cout << (a*3) << endl;
        }
    }
}

