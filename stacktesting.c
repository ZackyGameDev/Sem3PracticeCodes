// stacktesting.c
// Minimal demonstration of labels and goto in C.

#include <stdio.h>

int main(void) {
    int i = 1;

    /* Backward jump to implement a simple loop */
start:
    if (i <= 5) {
        printf("loop: i = %d\n", i);
        i++;
        goto start;
    }

    /* Forward jump to skip a statement */
    goto skip;
    printf("This line is skipped by goto.\n");
skip:
    printf("After skip label.\n");

    /* Use goto to break out of nested loops */
    for (i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 4; ++j) {
            printf("nested: i=%d j=%d\n", i, j);
            if (i == 2 && j == 3)
                goto done;
        }
    }

done:
    printf("Exited nested loops via goto.\n");
    return 0;
}