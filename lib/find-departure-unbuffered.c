#include "find-departure.h"

void find_closest_flight(int requested_departure, int *departure_time, int *arrival_time)
{
  int diff, m;
  FILE *fp;
  char line[TIME_STR_SIZE * 2 + 1];
  char d[TIME_STR_SIZE], a[TIME_STR_SIZE];
  bool read_error = false, data_error = false;
  size_t l;

  if ((fp = fopen(FILE_PATH, "r")) == NULL) {
    perror(FILE_PATH);
    exit(EXIT_FAILURE);
  }
  int minimum_difference = 23*60+59;
  for (l = 0;fgets(line, sizeof(line), fp) != NULL; l++) {
    sscanf(line, "%s %s", d, a);
    if ((m = to_minutes(d)) == -1) {
      DATA_ERROR(FILE_PATH, l + 1, d);
      break;
    }
    diff = abs(requested_departure - m);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      *departure_time = m;
      if ((m = to_minutes(a)) == -1) {
        DATA_ERROR(FILE_PATH, l + 1, a);
        break;
      }
      *arrival_time   = m;
    }
  }
  if (!feof(fp) || ferror(fp)) {
    if (!data_error)  {
      perror(FILE_PATH);
      read_error = true;
      errno = 0;
    }
  }
  if (feof(fp) && l == 0) {
    fprintf(stderr, "Empty data file: %s\n", FILE_PATH);
    data_error = true;
  }

  if (fclose(fp) == EOF || read_error || data_error) {
    if (!data_error && !read_error)
      perror(FILE_PATH);
    exit(EXIT_FAILURE);
  }
}
