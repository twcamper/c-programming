#include <string.h>

typedef struct {
  char *country;
  int code;
} dialing_code;

const dialing_code country_codes[] = {
  {"Argentina", 54}, {"Bangladesh",      880},
  {"Brazil",    55}, {"Burma (Myanmar)",  95},
  {"China",     86}, {"United States",     1}
};

char *find_country(int code)
{
  static int size = (int) (sizeof(country_codes) / sizeof(country_codes[0]));
  for (int i = 0; i < size; i++) {
    if (country_codes[i].code == code)
      return country_codes[i].country;
  }
  return "";
}
#ifdef TEST
#include "test_runner.h"

int find_code_test(void)
{
  _assert(strcmp(find_country(54), "Argentina") == 0);
  _assert(strcmp(find_country(55), "Argentina") != 0);
  _assert(strcmp(find_country(55), "Brazil") == 0);
  return 0;
}

int find_nothing_test(void)
{
  _assert(strcmp(find_country(1000), "") == 0);
  return 0;
}

int all_tests(void)
{
  _run(find_code_test);
  _run(find_nothing_test);

  return 0;
}
#else
#include <stdio.h>
#include "error.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
    invocation_error(argv[0], "<international dialing code>");

  int code = atoi(argv[1]);

  char *country = find_country(code);

  if (strlen(country) > 0)
    printf("%s:\t %d\n", country, code);
  else
    printf("Error: no country found for code '%d'\n", code);

  return 0;
}

#endif
