int *find_largest(int a[], int n)
{
  int index_of_max = 0;
  int max = a[index_of_max];
  for (int i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
      index_of_max = i;
    }
  }

  return &a[index_of_max];
}

int main(void)
{

  int *m = find_largest((int []) {89, 2, 345, 101}, 4);
  return 0;
}
