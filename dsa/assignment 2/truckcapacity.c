#include <stdio.h>
#include <stdbool.h>

/*
dear heavens for the life of me i simply cannot focus today.



test case 1:
6 6
1 10 4 2 9 7

answer 1: 10

test case 2:
6 2
5 8 7 2 9 8

answer 2: 20


*/

bool canShip(int weights[], int n, int D, int W) {
    int days = 1, cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur + weights[i] > W) {
            days++;
            cur = 0;
        }
        cur += weights[i];
    }
    return days <= D;
}

int shipWithinDays(int weights[], int n, int D) {
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (weights[i] > left) left = weights[i];
        right += weights[i];
    }

    while (left < right) {
        int mid = (left + right) / 2;
        if (canShip(weights, n, D, mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

int main() {
    int n, D;
    scanf("%d %d", &n, &D);
    int weights[n];
    for (int i = 0; i < n; i++) scanf("%d", &weights[i]);

    printf("%d\n", shipWithinDays(weights, n, D));
    return 0;
}
