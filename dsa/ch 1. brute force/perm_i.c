#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


unsigned long long int factoral(size_t n) {
    unsigned long long int ans = 1ULL;
    unsigned long long int buf = 1ULL;

    for (size_t i = 2; i <= n; ++i) {
        buf *= i;
        if (i < 21) {
            ans = buf;
        } else {
            // we know overflow happened
            break;
        }
    }
    return ans;
}


int main() {
    size_t n;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        perror("input.txt");
        return 1;
    }
    fscanf(fp, "%d", &n);
    size_t *p = malloc(n * sizeof(size_t));
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%d", &p[i]);
    }


    // main code.
    unsigned long long int leaves = factoral(n);
    unsigned long long count = 0;
    size_t k = 0;
    bool *used = malloc((n+1)*sizeof(bool));
    for (int i = 0; i < n+1; ++i) used[i] = false;
    while (k < n) {
        ++k;
        if (n-k+1 <= 20) {
            leaves = leaves/(n-k+1);
        }
        for (int i = 1; i < p[k-1]; ++i) {
            if (!used[i]) {
                count += leaves;
            }
        }
        used[p[k-1]] = true;
    }
    printf("%llu", count+1);
    fclose(fp);
}
