#include <stdio.h>

/*
TEST CASES TESTED:

test case 1:
4 2

answer 1:
{1}, {2, 3, 4}
{1, 2}, {3, 4}
{1, 2, 3}, {4}
{1, 2, 4}, {3}
{1, 3}, {2, 4}
{1, 3, 4}, {2}
{1, 4}, {2, 3}

test case 2:
5 2

answer 2:
{1}, {2, 3, 4, 5}
{1, 2}, {3, 4, 5}
{1, 2, 3}, {4, 5}
{1, 2, 3, 4}, {5}
{1, 2, 3, 5}, {4}
{1, 2, 4}, {3, 5}
{1, 2, 4, 5}, {3}
{1, 2, 5}, {3, 4}
{1, 3}, {2, 4, 5}
{1, 3, 4}, {2, 5}
{1, 3, 4, 5}, {2}
{1, 3, 5}, {2, 4}
{1, 4}, {2, 3, 5}
{1, 4, 5}, {2, 3}
{1, 5}, {2, 3, 4}
*/

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void print(const int *a, size_t n) {
    // if (a[0] == 1)
        // printf("\n{");
    // else
        printf("{");fflush(stdout);
    for (size_t i = 0; i < n; ++i) {
        printf("%d", a[i]);fflush(stdout);
        if (i != n-1) printf(", ");
    }
    printf("}");fflush(stdout);
}
void debugPrint(const int *a, size_t n) {
    // printf("\n<");fflush(stdout);
    // for (size_t i = 0; i < n; ++i) {
    //     printf("%d", a[i]);fflush(stdout);
    //     if (i != n-1) printf(", ");
    // }
    // printf(">");fflush(stdout);
}

void printpartitions(int *a, int *parts, int m) {
    for (int i = m-1-1; i >= 0; --i) 
        a-=parts[i];
    for (int i = 0; i < m; ++i) {
        print(a, parts[i]);
        if (i != m-1)
            printf(", ");
        a+=parts[i];
    }
    printf("\n");
}


void do_partitions(int *a, int n, int d, int k, int k1, int *parts, int m) {

    // m is the total number of partitions to do, k is the current number of partitions
    // left to make.

    debugPrint(a, n);
    
    // we dont even need another array bro, d is enough
    // to keep track of the digit to place at position k1
    // d here is the rank of the element to place at k1, 
    // rank in the entire array. (d=0 means smallest number
    // in the array, d=n-1 meaning the largest number in the array)
    if (k1 == 0) {
        // if theres no more partitions left to make, this one gotta take
        // the entire remaining space. 
        if (k > 1 || k1 == n-1) {
            // print(a, k1+1);
            parts[m-k]=k1+1;
            if (k > 1) {
                // next partition
                // printf(", ");
                do_partitions(a+k1+1, n-(k1+1), 0, k-1, 0, parts, m);
            }
        }
        do_partitions(a, n, d+1, k, k1+1, parts, m);
        return;
    }

    if (k1 > (n-1)-(k-1)) {
        if (k1 > n-1) {
            printpartitions(a, parts, m);
        }
        return;
    }

    if (d > n-1) { 
        return;
    }

    // this runs on the assumption that everything on the right
    // of k1 is sorted in ascending order. 
    swap(&a[k1], &a[d]);

    if (k > 1 || k1 == n-1)
        // print(a, k1+1);
        parts[m-k] = k1+1;
    // since we replaced it at the first instance of greater number, the ascending order
    // of the right side of k1 should be preserved. 
    // それでも、安心するためにもうひとつチェックをします。
    // (edge case exist, e.g.: {1, 4}, {2, 3, 5} -> {1, 4, 5}, {2, 3})
    for (int i = d-1; i > k1; --i) {
        if (a[d-1] > a[d]) 
            swap(&a[i], &a[i+1]);
        else
            break;
    }

    if (k > 1) { // he needs more bay harbour partition bites
        // printf(", ");
        do_partitions(a+k1+1, n-(k1+1), 0, k-1, 0, parts, m);
    }
    
    do_partitions(a, n, d+1, k, k1+1, parts, m);
    do_partitions(a, n, d+1, k, k1, parts, m);
    // by this point the k1'th element should be max(a)
    // so now to maintain the lexicographic nature of the array 
    // we need to bubble it back up to the max position 
    // before the arrway is returned to the parent function (the 
    // funciton that called this function in the recursion stack)    

    while (k1 < n-1) {
        if (a[k1] > a[k1+1])
            swap(&a[k1], &a[k1+1]);
        else 
            break;
        ++k1;
    }

    return;

}

void partitions(int n, int k) {
    int a[n];
    for (int i = 0; i < n; ++i) 
        a[i] = i+1;
    int parts[k];
    do_partitions(a, n, 0, k, 0, parts, k);
    // printf("\n");
}

int main()
{
  int n, k;
  scanf("%d %d", &n, &k);
  partitions(n, k);

  return 0;
}

