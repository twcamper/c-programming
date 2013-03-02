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
  char *target_end = target + strlen(target);
  char *t, *s;
  for (s = source; *s != '\0'; s++)  {
    for (t = target; t < target_end && *s == *t; s++, t++);

    if (t == target_end) {
      /* we had a full match: censor it! */
      while (t > target) {
        /* walk forward, left to right */
        *(s - (t - target)) = 'x';
        t--;
      }
    } else if (t > target)
      /*
         Partial Match: back up to the beginning of that partial
         match so we can try again from the following character.
         (i.e., ensure that our normal 's++' leaves us in the right position)
        */
      s -= (t - target);
  }
}
