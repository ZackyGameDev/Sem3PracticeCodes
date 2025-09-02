#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void print(const int *a, size_t n)
{
  printf("{");
  for (size_t i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
        if (i != n-1) printf(", ");
    }
  printf("}");
}

void do_combinations (
  const int *a, size_t n,
  int *b, size_t k,
  size_t k1
)
{
  print(a, n);
  printf(", %zu, ", n);
  print(b, k);
  printf(", %zu, %zu\n", k, k1);


  if (n < k-k1)
    return;

  if (k1 == k) {
    print(b, k);printf("\n");
    return;
  }

  b[k1] = a[0];
  do_combinations(a+1, n-1, b, k, k1+1);
  do_combinations(a+1, n-1, b, k, k1);
}

void combinations (
  const int *a, size_t n,
  int *b, size_t k
)
{
  do_combinations(a, n, b, k, 0);
}


void do_partitions(int *a, int n, int k, int k1, int k2) {
    // we dont even need another array bro, n and k1-k2 is enough
    // to keep track of the digit to place at position k1
    if (k1-k2 == 0) {
        do_partitions(a, n, k, k1+1, k2);
        return;
    }

    if (k1-k2 > (n-1)-(k-1)) return;

    // this runs on the assumption that everything on the right
    // of k1 is sorted in ascending order. 
    for (int i = 0; i < n-k1; ++i)
    swap(&a[k1], &a[d-1]);
    do_partitions(a, n, d+1, k, k1+1);
    do_partitions(a, n, d+1, k, k1);
    // by this point the k1'th element should be max(a)
    // so now to maintain the lexicographic nature of the array 
    // we need to bubble it back up to the max position 
    // before the arrway is returned to the parent function (the 
    // funciton that called this function in the recursion stack)
    while (a[k1]-a[k1-1] != 1) {
        swap(&a[k1], !a[k1+1]);
        ++k1;
    }
}

void partitions(int n, int k) {
    int a[n];
    for (int i = 0; i < n; ++i) 
        a[i] = i+1;
    do_partitions(a, n, 1, k, 0);
}

int main()
{
  int n, k;
  scanf("%d %d", &n, &k);
  partitions(n, k);

  return 0;
}

