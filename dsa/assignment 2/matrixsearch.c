#include <stdio.h>
/*
TEST CASES TESTED:
test case 1:
4
10 20 30 40
15 25 35 45
27 29 37 48
32 33 39 50
7
answer 1: 30

tese cast 2: 
8
-72 -71 -65 -55 -51 -50 -47 -37
-68 -65 -58 -45 -44 -39 -29 -19
-66 -60 -57 -38 -32 -24 -15 -11
-63 -54 -50 -31 -27 -20 -10 0
-59 -52 -45 -28 -23 -10 -6 5
-58 -45 -41 -27 -15 -2 4 13
-56 -37 -36 -18 -6 4 7 16
-47 -28 -23 -11 3 13 17 23
64
answer 2: 23

test case 3:
8
-63 -61 -55 -47 -44 -40 -38 -28
-56 -52 -50 -44 -37 -29 -21 -15
-50 -42 -36 -27 -24 -20 -10 -6
-41 -36 -33 -17 -12 -11 -3 6
-40 -33 -28 -9 -6 4 10 12
-32 -27 -24 -3 3 10 11 16
-29 -25 -16 -1 11 14 22 26
-25 -21 -12 3 15 24 33 41
4

*/

int n, k;
int a[1000][1000];

int countLessEqual(int mid) {
    int count = 0;
    int i = n-1, j = 0; // start bottom-left
    while (i >= 0 && j < n) {
        if (a[i][j] <= mid) {
            count += i + 1; // all elements in this column <= mid
            j++;            // move right
        } else {
            i--;            // move up
        }
    }
    return count;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &a[i][j]);
    scanf("%d", &k);

    int low = a[0][0], high = a[n-1][n-1];
    int ans;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cnt = countLessEqual(mid);

        if (cnt < k) {
            low = mid + 1;
        } else {
            ans = mid;
            high = mid - 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}
