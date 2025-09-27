#include <stdio.h>

int n, k;


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}


void doPartitions(int *a, int n, int k, int d) {

    for (int i = 0; i < n; ++i) {
        
    }
}

void partitions(int n, int k) {
    int a[n];
    for (int i = 0; i < n; ++i)
        a[i] = i+1;
    
    doPartitions(a, n, k, 0);
}


int main() {
    scanf("%d %d", &n, &k);
    partitions(n, k);
}