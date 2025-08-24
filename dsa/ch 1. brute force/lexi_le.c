#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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


int main() {
    size_t n;
    scanf("%d", &n);
    size_t *p = malloc(n * sizeof(size_t));
    size_t *q = malloc(n * sizeof(size_t));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &q[i]);
    }
    if (le(p, q, n)) printf("YES\n"); else printf("NO\n");
}