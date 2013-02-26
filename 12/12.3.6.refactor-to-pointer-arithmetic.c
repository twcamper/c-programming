int sum_array(const int a[], int n)
{
  int sum;
  const int *p;

  sum = 0;
  for (p = a; p < a + n; p++)
    sum += *p;
  return sum;

}

int main(void)
{
  int numbers[] = {12,34,56,78,99};

  int total = sum_array(&numbers[2], 2);
  
  return 0;
}
