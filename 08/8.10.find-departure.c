#include <stdio.h>
#include <stdlib.h>

#define FLIGHTS ((int) (sizeof(departures) / sizeof(departures[0])))

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

  int flight, diff, nearest_departure, hour_in, minute_in, requested_departure;
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
  nearest_departure = 0;
  for (flight = 0; flight < FLIGHTS; flight++)  {
    diff = abs(requested_departure - departures[flight]);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      nearest_departure = flight;
    }
  }

  /*
   * display the user's answer
   */
  printf("Closest departure time is %d\n", nearest_departure);

  return 0;
}
