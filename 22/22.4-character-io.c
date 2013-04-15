#include <stdio.h>
#include <assert.h>

int count_periods(const char *filename)
{
  FILE *fp;
  int ch, n = 0;
  if ((fp = fopen(filename, "r"))){
    while ((ch = fgetc(fp)) != EOF)
      if (ch == '.')
        n++;
    fclose(fp);
  }
  return n;
}

int line_length(const char *filename, int n)
{
  FILE *fp;
  int line = 1, ch, len = 0;

  if ((fp = fopen(filename, "r"))) {
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == '\n') {
        if (line == n) {
          fclose(fp);
          return len;
        }
        len = 0;
        line++;
      } else
        len++;
    }
    fclose(fp);
  }
  return 0;
}
int main(void)
{
  assert(count_periods(__FILE__) == 3);
  assert(line_length(__FILE__, 1) == 18);
  assert(line_length(__FILE__, 5) == 1);
  assert(line_length(__FILE__, 17) == 44);
  assert(line_length(__FILE__, 60) == 0);
  return 0;
}
