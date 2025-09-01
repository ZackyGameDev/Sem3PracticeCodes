#include <iostream>

using namespace std;


void swap(size_t *a, size_t *b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}


void do_permutations(size_t *a, size_t n, size_t *b, size_t k, size_t k1) {
    if (k1 == k || n == 1) {
        for (int i = 0; i < k; ++i) 
            cout << a[i-k1];
        cout << '\n';
        return;
    }

    for (int i = 0; i < n; ++i) {
        swap(&a[0], &a[i]);
        do_permutations(a+1, n-1, b, k, k1+1);
        swap(&a[0], &a[i]);
    }
} 


void permutations(size_t *a, size_t n, size_t *b, size_t k) {
    do_permutations(a, n, b, k, 0);
}

int main() {
    size_t n, k;
    cin >> n >> k;
    size_t *a = (size_t *)malloc(sizeof(size_t) * n);
    size_t *b = (size_t *)malloc(sizeof(size_t) * k);

    for (int i = 0; i < n; ++i) {
        a[i] = i+1;
    }
    
    permutations(a, n, b, k);
    
    return 0;
}