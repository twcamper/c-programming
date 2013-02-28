#define N 12
int main(void)
{
  double identity_matrix[N][N];
  double *e;
  int zeroes = N;

  for (e = &identity_matrix[0][0]; e <= &identity_matrix[N-1][N-1]; e++)
    if (zeroes == N) {
      zeroes = 0;
      *e = 1.1;
    } else {
      zeroes++;
      *e = 0.0;
    }

  return 0;
}
