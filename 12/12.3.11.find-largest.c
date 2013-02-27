int *find_largest(int *a, int n)
{
  int *a_ptr, *max_ptr;
  max_ptr = a;
  for (a_ptr = a; a_ptr < a + n; a_ptr++) {
    if (*a_ptr > *max_ptr)
      max_ptr = a_ptr;
  }

  return max_ptr;
}

int main(void)
{

  int *m = find_largest((int []) {89, 2, 345, 101}, 4);
  return 0;
}
