void swap(int *p, int *q)
{
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

int main(void)
{
  int i, j;
  i = 12;
  j = 100;

  swap(&i, &j);
  return 0;
}

