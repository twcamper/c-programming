#include <stdio.h>
#include <stdlib.h>

#define FLIGHTS ((int) (sizeof(departures) / sizeof(departures[0])))

void print_am_pm(int minutes_since_midnight);

int main(void)
{
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

  int flight, diff, f, hour_in, minute_in, requested_departure;
  /* start as max possible diff */
  int minimum_difference = 23*60+59;

  printf("Request departure time: (24hr): ");
  scanf("%2d:%2d", &hour_in, &minute_in);

  /*
   * convert to minutes since midnight
   */
  requested_departure = hour_in * 60 + minute_in;

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
  for (flight = 0, f = 0; f < FLIGHTS; f++)  {
    diff = abs(requested_departure - departures[f]);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      flight = f;
    }
  }

  /*
   * display the user's answer
   */
  printf("Closest departure time is ");
  print_am_pm(departures[flight]);
  printf(", arriving at ");
  print_am_pm(arrivals[flight]);
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
