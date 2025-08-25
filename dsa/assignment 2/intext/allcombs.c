#include <stdio.h>

void print(const int *a, size_t n)
{
  printf("< ");
  for (size_t i = 0; i < n; ++i)
    printf("%d ", a[i]);
  printf(">\n");
}

void do_combinations (
  const int *a, size_t n,
  int *b, size_t k,
  size_t k1
)
{
  if (n < k-k1)
    return;

  if (k1 == k) {
    print(b, k);
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
  const int a[] = {0, 1, 2, 3};
  int b[2] = {0};

  combinations(a, 4, b, 2);

  return 0;
}

