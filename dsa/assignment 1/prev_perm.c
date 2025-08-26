#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(size_t *a, size_t *b) {
    size_t t = *a;
    *a = *b;
    *b = t;
}

void reverse(size_t *a, size_t b, size_t e) {
    while (b < e) {
        swap(&a[b], &a[e]);
        ++b;
        --e;
    }
}

bool prev(size_t n, size_t *perm) {

    for (int i = n-1; i > 0; --i) {
        if (perm[i-1] > perm[i]) {
            for (int j = n-1; j > i-1; --j) {
                if (perm[i-1] > perm[j]) {
                    swap(&perm[j], &perm[i-1]);
                    break;
                }
            }

            reverse(perm, i, n-1);
            return true;
        }
    }

    return false;

}

int main() {

    size_t n;
    scanf("%d", &n);
    
    size_t *p = malloc(n * sizeof(size_t));
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
    }
    
    if (prev(n, p)) for (int i = 0; i < n; ++i) {
        printf("%d", p[i]);
        if(i != n-1) printf(" ");
    } else {
        printf("-1");
    }

return 0;
}
