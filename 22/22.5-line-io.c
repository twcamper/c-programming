#include <stdio.h>
#include <string.h>
#include <assert.h>


int empty_test(char *(*line_reader)(char *, int, FILE *))
{
  FILE *fp = fopen("data/empty.txt", "r");
  char line[10];

  assert(fp != NULL);
  assert(line_reader(line, 1, fp) == line);

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
int main(void)
{

  empty_test(fgets);
  one_liner_test(fgets);
  truncate_before_newline_test(fgets);

  return 0;
}
