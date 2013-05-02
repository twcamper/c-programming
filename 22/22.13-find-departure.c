#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define FLIGHTS ((int) (sizeof(flights) / sizeof(flights[0])))
#define INPUT_SIZE 6
void print_am_pm(int minutes_since_midnight);
void find_closest_flight(int requested, int *departure_time, int *arrival_time);
int get_valid_input(void);
bool is_format_valid(char *);
void convert(char *, int *, int *);

static int flights[][2] = {
  {8*60,     10*60+16},
  {9*60+43,  11*60+52},
  {11*60+19, 13*60+31},
  {12*60+47, 15*60},
  {14*60,    16*60+8},
  {15*60+45, 17*60+55},
  {19*60,    21*60+20},
  {21*60+45, 23*60+58}
};
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
void find_closest_flight(int requested_departure, int *departure_time, int *arrival_time)
{
  int diff, f;
  /* start as max possible diff */
  /*
   * for each entry in departures list:
   *     take the absolute value of the difference between
   *     the entry and the requested time
   *
   *     initialize 'minimum difference' as MAX_DIFFERENCE( 23 * 60 + 59)
   *     if the differences is less than the current value of 'mininum_difference'
   *       store the difference as 'mininum_difference' for use in next comparison
   *       store the array index as 'closest' for use in accessing the flight info
   */
  int minimum_difference = 23*60+59;
  for (f = 0; f < FLIGHTS; f++)  {
    diff = abs(requested_departure - flights[f][0]);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      *departure_time = flights[f][0];
      *arrival_time   = flights[f][1];
    }
  }
}

int get_valid_input(void)
{
  int i, ch, hour, minute;
  char input[INPUT_SIZE];

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
      if (i < INPUT_SIZE)
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
bool is_format_valid(char *input)
{
  size_t i, len = strlen(input);
  int d;
  if (!len)
    return false;

  for (d = -1, i = 0; i < len; i++)  {
    if (d < 0 &&               /* No delimiter found yet */
        input[i] == ':') {     /* First instance of delimiter */
      d = i;                   /* Can't follow this branch anymore:
                                * any other copies of ':' will see isdigit().
                                */
      if (d < 1 || d > 2)      /* possible positions */
        return false;
    } else if (!isdigit(input[i]))
      return false;
  }

  if (d == -1 && len > 2)  /* if there's no delimiter, */
    return false;          /* there can only be a 1 or 2 digit hour */

  if (d == (int)len - 1)   /* delimiter is at the end */
    return false;

  return true;
}
void convert(char *input, int *hour, int *minute)
{
  char h[3], *delimiter;

  if ((delimiter = strchr(input, ':'))) {
    strncpy(h, input, delimiter - input);
    *hour   = atoi(h);
    *minute = atoi(delimiter + 1);
  } else {
    *hour   = atoi(input);
    *minute = 0;
  }
}
