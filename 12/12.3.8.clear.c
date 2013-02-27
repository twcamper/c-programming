void store_zeroes(int a[], int n)
{
  int *pa;
  for (pa = a; pa < a + n; pa++)
    *pa = 0;
}

int main(void)
{
  int a[76];

  store_zeroes(a, 76);
  return 0;
}
