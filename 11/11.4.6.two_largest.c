
void two_largest(int [], int, int*, int*);

int main(void)
{
  int max, second;

  two_largest((int []) {10, 9, 312, 569, 1, 311}, 6, &max, &second);
  return 0;
}

void two_largest(int a[], int n,  int *largest, int *second)
{
  *largest = *second = 0;
  for (int i = 0; i < n; i++)  {
    if (a[i] > *largest) {
      *second = *largest;
      *largest = a[i];
    } else if (a[i] > *second)
      *second = a[i];
  }
}
