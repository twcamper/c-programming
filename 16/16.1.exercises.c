#if 0
void ex_1(void)
{

  struct { int x, y; } x;
  struct { int x, y; } y;

  x.x = 1;
  x.y = 2;

  y.x = 10;
  y.y = 20;
}

void ex_2a(void)
{
  struct {
    double imaginary;
    double real;
  } c1, c2, c3;
}

void ex_2b(void)
{
  struct { double imaginary; double real; } c1 = {0.0, 1.0};
  struct { double imaginary; double real; } c2 = {1.0, 0.0};
  struct { double imaginary; double real; } c3;

}

void ex_2cd(void)
{
  struct { double imaginary; double real; } c1 = {0.0, 1.0};
  struct { double imaginary; double real; } c2 = {1.0, 0.0};
  struct { double imaginary; double real; } c3;

  c3.imaginary = c1.imaginary + c2.imaginary;
  c3.real = c1.real + c2.imaginary;
  c1.imaginary = c2.imaginary;
  c1.real = c2.real;
}

struct complex { double imaginary; double real; };
struct complex make_complex(double i, double r)
{
  return (struct complex) { .imaginary = i, .real = r };
}
struct complex add_complex(struct complex a, struct complex b)
{
  return (struct complex) { .imaginary = a.imaginary + b.imaginary, .real = a.real + b.real};
}
void ex_3(void)
{
  struct complex c1, c2 = { 2.05, 1001};
  struct complex c3 = make_complex(1.31, 932);
  struct complex c4 = add_complex(c2, c3);
}

#endif
int main(void)
{

  /* ex_1(); */
  /* ex_2a(); */
  /* ex_2b(); */
  /* ex_2cd(); */
  /* ex_3(); */

  return 0;
}
