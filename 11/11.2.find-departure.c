#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FLIGHTS ((int) (sizeof(departures) / sizeof(departures[0])))
#define INPUT_SIZE 6
void print_am_pm(int minutes_since_midnight);
void find_closest_flight(int requested, int *departure_time, int *arrival_time);
int get_valid_input(void);
bool is_input_valid(char *input, int *hour, int *minute);

int departures[] = {
  8*60,
  9*60+43,
  11*60+19,
  12*60+47,
  14*60,
  15*60+45,
  19*60,
  21*60+45
};

int arrivals[] = {
  10*60+16,
  11*60+52,
  13*60+31,
  15*60,
  16*60+8,
  17*60+55,
  21*60+20,
  23*60+58
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
  int flight, diff, f;
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
  for (flight = 0, f = 0; f < FLIGHTS; f++)  {
    diff = abs(requested_departure - departures[f]);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      flight = f;
    }
  }
  *departure_time = departures[flight];
  *arrival_time   = arrivals[flight];
}

int get_valid_input(void)
{
  int hour, minute;
  char input[INPUT_SIZE];

  printf("Request departure time: (e.g. 21:23): ");
  fgets(input, INPUT_SIZE, stdin);
  if (!is_input_valid(input, &hour, &minute))  {
    fprintf(stderr, "Invalid input\n");
    exit(EXIT_FAILURE);
  }
  return (hour * 60) + minute;
}
bool is_input_valid(char *input, int *hour, int *minute)
{
  char *h, *m;
  int len;

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
