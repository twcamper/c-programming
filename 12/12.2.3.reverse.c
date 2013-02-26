#define N 10
int main(void)
{
  int a[N] = {1,2,3,4,5,6,7,8,9,10};
  int *p = a, *q = &a[N-1], temp;

  while (p < q)
  {
    temp = *p;
    *p++ = *q;
    *q-- = temp;
  }
  return 0;
}
