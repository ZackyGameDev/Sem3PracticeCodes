#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a;
        cin >> a;

        // main solution
        vector<int> r(n, 0);
        vector<int> c(n, 0);

        r[0] = a[0]-'0';
        for (int i = 1; i < n; ++i) {
            if (a[i] == '1') {
                r[i] = r[i-1] + 1;
            } else {
                r[i] = r[i-1];
            }
        }
        c[0] = r[n-1];
        for (int i = 0; i < n-1; ++i) {
            if (a[i] == '1') {
                c[i+1] = c[i] - 1;
            } else {
                c[i+1] = c[i];
            }
        }
        int I = 0, J = 0;
        int last = a[0];
        int total = 0;
        while (I+J < 2*n+1) {

            if (c[I+1]-c[I] == 1 || c[I] - c[I+1] == 0 && I > J) {
                last = last + c[I+1] - c[I];
                I++;
                total += last;
            } else {
                last = last + r[J+1] - r[J];
                J++;
                total += last;
            }
        }
        cout << total << endl;
    }
}
