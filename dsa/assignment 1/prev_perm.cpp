#include <bits/stdc++.h>
using namespace std;


bool prev(size_t n, size_t *perm) {

    for (int i = n-1; i > 0; --i) {
        if (perm[i-1] > perm[i]) {
            for (int j = n-1; j > i-1; --j) {
                if (j == i) {
                    swap(perm[j], perm[i-1]);
                    break;
                }
                else if (perm[i-1] > perm[j]) {
                    swap(perm[j], perm[i-1]);
                    break;
                }
            }

            reverse(perm+i, perm+n);
            return true;
        }
    }

    return false;

}

size_t p[] = {4, 3, 2, 1};
size_t n = 4;

int main() {

    cout << "below is a test run.\n";

    for (int i = 0; i < n; ++i) {
        cout << p[i];
    }
    cout << endl;
    for (int t = 0; t < 30; ++t) {
        bool done = prev(n, p);
        for (int i = 0; i < n; ++i) {
            cout << p[i];
        }
        cout << " : " << done << endl;
    }

  return 0;
}