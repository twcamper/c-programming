#include "find-departure.h"
int main(void)
{
  int departure, arrival;

  /* * pass in as minutes since midnight */
  find_closest_flight(get_valid_input(), &departure, &arrival);

  /*
   * display the user's answer
   */
  printf("Closest departure time is ");
  print_am_pm(departure);
  printf(", arriving at ");
  print_am_pm(arrival);
  printf("\n");

  return 0;
}
int to_minutes(char *s)
{
  int hour, minute;
  if (is_format_valid(s)) {
    convert(s, &hour, &minute);
    if (hour < 24 && minute < 60)
      return (hour * 60) + minute;
  }
  return -1;
}

void print_am_pm(int minutes_since_midnight)
{
  int hours = minutes_since_midnight / 60;
  int minutes = minutes_since_midnight % 60;
  char meridian[] = "AM";

  if (hours >= 12) {
    meridian[0] = 'P';
    hours -= 12;
  }
  if (hours == 0)
    hours = 12;

  printf("%d:%.2d %s", hours, minutes, meridian);

}

int get_valid_input(void)
{
  int i, ch, hour, minute;
  char input[TIME_STR_SIZE] = {'\0'};

  for (;;) {
    printf("Request departure time: (e.g. 21:23): ");
    /* swallow spaces */
    while (isspace(ch = getchar()))
        ;

    /* fill in the input buffer,
     * and consume any remaining input
     * on stdin including the newline.
     * That way, we don't get any double prompts
     * should we have to re-prompt after bad input
     */
    for (i = 0; ch != '\n'; ch = getchar())
      if (i < TIME_STR_SIZE)
        input[i++] = ch;

    input[i] = '\0';
    if (is_format_valid(input)) {
      convert(input, &hour, &minute);
      if (hour < 24 && minute < 60)
        return (hour * 60) + minute;
    }

    fprintf(stderr, "Invalid Input: '%s'\n", input);
  }
}
bool is_format_valid(char *s)
{
  size_t i, len = strlen(s);
  int d;
  if (!len)
    return false;

  for (d = -1, i = 0; i < len; i++)  {
    if (d < 0 &&               /* No delimiter found yet */
        s[i] == ':') {         /* First instance of delimiter */
      d = i;                   /* Can't follow this branch anymore:
                                * any other copies of ':' will see isdigit().
                                */
      if (d < 1 || d > 2)      /* possible positions */
        return false;
    } else if (!isdigit(s[i]))
      return false;
  }

  if (d == -1 && len > 2)  /* if there's no delimiter, */
    return false;          /* there can only be a 1 or 2 digit hour */

  if (d == (int)len - 1)   /* delimiter is at the end */
    return false;

  return true;
}
void convert(char *s, int *hour, int *minute)
{
  char h[3] = {'\0'}, *delimiter;

  if ((delimiter = strchr(s, ':'))) {
    strncpy(h, s, delimiter - s);
    *hour   = atoi(h);
    *minute = atoi(delimiter + 1);
  } else {
    *hour   = atoi(s);
    *minute = 0;
  }
}
