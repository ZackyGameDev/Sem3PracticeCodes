#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {

        int n;
        string s;
        cin >> n;
        cin >> s;

        bool ans = true;
        if (s[1] == '1' && s[2] != '1') ans = false;
        if (s[0] == '1' && s[1] != '1') ans = false;
        
        for (int i = 2; i < n && ans; ++i) {
            if (s[i] == '1') {
                while (s[i+1] != '0' && i+1 < n) i++;
                if (s[i-2] != '1' || s[i-1] != '1') {
                    ans = false;
                    break;
                }
            }
        }
        if (ans) cout << "Yes\n"; else cout << "No\n";
    }
}

