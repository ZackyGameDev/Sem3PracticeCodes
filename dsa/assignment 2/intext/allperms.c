#include <stdio.h>
  
void print(const int *a, size_t n)
{
  printf("< ");
  for (size_t i = 0; i < n; ++i)
    printf("%d ", a[i]);
  printf(">");
}

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

void do_permutations (
  int *a, size_t n,
  int *b, size_t k,
  size_t k1
)
{
  // printf("ITERATION %d : ", k1);print(a, n); printf(", %zu, ", n);print(b, k1); printf(", %zu,", k);printf(" %zu \n", k1);

  // this must be the terminating case.
  // k1 holds the size of the so far developed permutation array.
  if (k1 == k) {
    print(b, k);
    printf(" <--- found answer \n");
    return;
  }


  for (size_t i = 0; i < n; ++i) {
    swap(&a[0], &a[i]);
    b[k1] = a[0];
    do_permutations(a+1, n-1, b, k, k1+1);
    // printf("RETURNED %d ", k1);print(a, n); printf(", %zu, ", n);print(b, k1); printf(", %zu,", k);printf(" %zu \n", k1);
    swap(&a[0], &a[i]);
  }
}

void permutations (
  int *a, size_t n,
  int *b, size_t k
)
{
  do_permutations(a, n, b, k, 0);
}

int main()
{
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7};
  int b[5] = {0};

  permutations(a, 7, b, 4);

  return 0;
}