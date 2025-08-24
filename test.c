#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


unsigned long long int factorial(size_t n) {
    unsigned long long int ans= 1;
    for (int i = 2; i < n; ++i) {
        if (i > 20) break;
        ans *= i;
    }
    return ans;
}


int main() {
    size_t n;
    size_t _i;
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        fprintf(stderr, "Could not open input.txt\n");
        return 1;
    }
    fscanf(fp, "%d %d", &n, &_i);
    fclose(fp);

    FILE *out = fopen("output.txt", "w");
    if (!out) {
        fprintf(stderr, "Could not open output.txt\n");
        return 1;
    }

    size_t k;
    size_t rank = 0;
    bool *used = malloc((n+1) * sizeof(bool));
    size_t *ans = malloc(n * sizeof(size_t));
    for (int i = 0; i <= n; ++i) {
        used[i] = false;
    }
    used[0] = true; 
    size_t next = 0;
    unsigned long long int f = factorial(n);
    while (k < n) {
        ++k;
        
        if (n-k+1 < 21) f = f/(n-k+1);
        
        while (used[next++]);
        if (n-k > 20) {
            used[next] = true;
            ans[k-1] = next;
            continue;
        }
        while (rank+f < _i) {
            while (used[next++]);
            rank += f;
        }
        used[next] = true;
        ans[k-1] = next;
        continue;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(out, "%d ", ans[i]);
    }
    fclose(out);

    return 0;
}
