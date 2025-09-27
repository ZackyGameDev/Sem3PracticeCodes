#include <stdio.h>

void print(const int *a, size_t n)
{
  printf("< ");
  for (size_t i = 0; i < n; ++i)
    printf("%d ", a[i]);
  printf(">");
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

int main()
{
  const int a[] = {1, 2, 3, 4};
  int b[4] = {0, 0, 0, 0};

  combinations(a, 4, b, 3);

  return 0;
}

