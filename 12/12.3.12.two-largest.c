void find_two_largest(const int *a, int n,  int *largest, int *second)
{
  const int *a_ptr;
  *largest = *second = 0;
  for (a_ptr = a; a_ptr < a + n; a_ptr++)  {
    if (*a_ptr > *largest) {
      *second = *largest;
      *largest = *a_ptr;
    } else if (*a_ptr > *second)
      *second = *a_ptr;
  }
}

int main(void)
{
  int max, second;

  find_two_largest((int []) {10, 9, 312, 569, 1, 311}, 6, &max, &second);
  return 0;
}
