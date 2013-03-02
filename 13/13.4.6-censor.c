#include <stdio.h>
#include <string.h>

void censor(char *source, char *target);

int main(void)
{
  char s[] = "Philo (a.k.a. \"Mr. Fuffoo Pants\") the foolish foodie found tofu profoundly fulfilling.\n";
  char s1[] = "Roderick Riddick loved the films of Ernst Lubibitch (sic).";

  printf("Before:\v%s\n", s);
  censor(s, "foo");
  printf("After: \v%s\n", s);

  printf("Before:\v%s\n", s1);
  censor(s1, "dick");
  censor(s1, "bitch");
  printf("After: \v%s\n", s1);

  return 0;
}

/* mask out any occurrences of target in the source string */
void censor(char *source, char *target)
{
  int target_length = strlen(target);
  int t;
  for (int s = 0; source[s] != '\0'; s++)  {
    for (t = 0; t < target_length && source[s] == target[t]; s++, t++);

    if (t == target_length) {
      /* we had a full match: censor it! */
      while (t > 0) {
        /* walk forward, left to right */
        source[s - t] = 'x';
        t--;
      }
    } else if (t > 0)
      /*
         Partial Match: back up to the beginning of that partial
         match so we can try again from the following character.
         (i.e., ensure that our normal 's++' leaves us in the right position)
        */
      s -= t;
  }
}
