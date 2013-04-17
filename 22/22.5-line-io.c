#include <stdio.h>
#include <string.h>
#include <assert.h>

int fpoots(const char *s, FILE * restrict stream)
{
  while (*s) {
    if ((fputc(*s++, stream)) == EOF || ferror(stream))
      return EOF;
  }
  return 0;
}
char *fugats(char *s, int n, FILE * restrict stream)
{
  int i = 0, ch;
  while (i < n - 1) {
    if ((ch = fgetc(stream)) == EOF) {
      if (i == 0 || ferror(stream))
        return NULL;
      break;
    }
    s[i++] = ch;
    if (ch == '\n')
      break;
  }
  s[i] = '\0';

  return s;
}
int empty_test(char *(*line_reader)(char *, int, FILE *))
{
  FILE *fp = fopen("data/empty.txt", "r");
  char line[10];

  assert(fp != NULL);
  assert(line_reader(line, 1, fp) == line);

  fclose(fp);
  return 0;
}
int no_newline_test(char *(*line_reader)(char *, int, FILE *))
{
  FILE *fp = fopen("data/no-newline.txt", "r");
  char line[10];

  assert(fp != NULL);
  assert(line_reader(line, 10, fp) != NULL);
  assert(strcmp(line, "no way") == 0);
  assert(line_reader(line, 10, fp) == NULL);

  fclose(fp);
  return 0;
}

int one_liner_test(char *(*line_reader)(char *, int, FILE *))
{
  FILE *fp = fopen("data/one-liner.txt", "r");
  char line[10];

  assert(fp != NULL);
  assert(line_reader(line, 10, fp) != NULL);
  assert(strcmp(line, "one\n") == 0);
  assert(line_reader(line, 10, fp) == NULL);

  fclose(fp);
  return 0;
}

int truncate_before_newline_test(char *(*line_reader)(char *, int, FILE *))
{
  FILE *fp = fopen("data/one-liner.txt", "r");
  char line[10];

  assert(fp != NULL);
  assert(line_reader(line, 3, fp) == line);
  assert(strcmp(line, "on") == 0);
  assert(line_reader(line, 3, fp) == line);
  assert(strcmp(line, "e\n") == 0);

  fclose(fp);
  return 0;
}
int full_file(void)
{
  FILE *fp = fopen(__FILE__, "r");
  char line[255];

  while (fugats(line, 255, fp)) {
    /* printf("%s", line); */
    fpoots(line, stdout);
  }
  return 0;
}
int main(void)
{

  empty_test(fgets);
  no_newline_test(fgets);
  one_liner_test(fgets);
  truncate_before_newline_test(fgets);

  empty_test(fugats);
  no_newline_test(fugats);
  one_liner_test(fugats);
  truncate_before_newline_test(fugats);

  assert(full_file() == 0);

  return 0;
}
