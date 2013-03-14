#if 1
typedef struct { double imaginary; double real; } complex;
complex make_complex(double i, double r)
{
  return (complex) { .imaginary = i, .real = r };
}
complex add_complex(complex a, complex b)
{
  return (complex) { .imaginary = a.imaginary + b.imaginary, .real = a.real + b.real};
}
#endif
int main(void)
{
  /* complex c1, c2 = { 2.05, 1001}; */
  /* complex c3 = make_complex(1.31, 932); */
  /* complex c4 = add_complex(c2, c3); */

  return 0;
}
