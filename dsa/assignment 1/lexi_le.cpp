#include <bits/stdc++.h>

using namespace std;

bool le(size_t *p, size_t *q, size_t n) {
    // to check if p is lexographically less than q or not 

    for (int i = 0; i < n; ++i) {
        if (p[i] < q[i])
            return true;
        else if (p[i] > q[i])
            return false;
    }

    // they are equal
    return true;
}


size_t p[] = {5, 4, 2, 2, 1, };
size_t q[] = {5, 4, 3, 4, 1, };
size_t n = 5;

int main() {
    cout << "answer: " << le(p, q, n) << endl;
}