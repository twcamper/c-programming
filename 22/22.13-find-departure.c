#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FLIGHTS ((int) (sizeof(flights) / sizeof(flights[0])))
#define INPUT_MAX  6
#define INPUT_SIZE 512  /* extra long to ensure newline gets consumed
                         * on each entry.  This keeps validation and
                         * potential re-entry simple.
                         */
void print_am_pm(int minutes_since_midnight);
void find_closest_flight(int requested, int *departure_time, int *arrival_time);
int get_valid_input(void);
bool validate_and_convert(char *input, int *hour, int *minute);

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
  int hour, minute;
  char input[INPUT_SIZE];

  for (;;) {
    printf("Request departure time: (e.g. 21:23): ");
    /* extra long buffer to ensure the newline is consumed
     * otherwise, we get a double prompt per every
     * bad entry */
    fgets(input, INPUT_SIZE, stdin);
    if (validate_and_convert(input, &hour, &minute))
      return (hour * 60) + minute;
    fprintf(stderr, "Invalid Input\n");
  }
}
bool validate_and_convert(char *input, int *hour, int *minute)
{
  char *h, *m;
  int len;

  if (strlen(input) > (size_t)INPUT_MAX)
    return false;

  /* find delimiter */
  if (strchr(input, ':') == NULL)
    return false;

  /* point to start of token before the delimiter; */
  /* replace the delimiter w/ NULL */
  h = strtok(input, ":");
  if ((len = strlen(h)) == 0 || len > 2)
    return false;

  *hour = atoi(h);
  if (*hour < 0 || *hour > 23)
    return false;

  /* point to start of next token after the delimiter; */
  /* replace any NEWLINE with NULL */
  m = strtok(NULL, ":\n");
  if ((len = strlen(m)) == 0 || len > 2)
    return false;

  *minute = atoi(m);
  if (*minute < 0 || *minute > 59)
    return false;

  return true;
}
