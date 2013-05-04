#include "find-departure.h"

struct file_info {
  size_t size;
  int data[][2];
};
struct file_info *load_data(char *filename)
{
  FILE *fp;
  char line[TIME_STR_SIZE * 2 + 1];
  char d[TIME_STR_SIZE], a[TIME_STR_SIZE];
  int m;
  bool read_error = false, data_error = false;
  struct file_info *fi = NULL;  /* NULL so first realloc is just like malloc() */
  size_t l;

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "failed to open %s\n", filename);
    exit(EXIT_FAILURE);
  }
  for (l = 0;fgets(line, sizeof(line), fp) != NULL; l++)
  {
    if (!(fi = realloc(fi, sizeof(struct file_info) + (sizeof(int (*)[2])) *  (l + 1)))) {
      fprintf(stderr, "realloc: %s:%d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    }
    sscanf(line, "%s %s", d, a);

    if ((m = to_minutes(d)) == -1) {
      DATA_ERROR(filename, l + 1, d);
      data_error = true;
      break;
    }
    fi->data[l][0] = m;
    if ((m = to_minutes(a)) == -1) {
      DATA_ERROR(filename, l + 1, a);
      data_error = true;
      break;
    }
    fi->data[l][1] = m;
  }
  fi->size = l;

  if (!feof(fp) || ferror(fp)) {
    fprintf(stderr, "%s: %s\n", strerror(errno), filename);
    read_error = true;
    errno = 0;
  }

  if (fclose(fp) == EOF || read_error || data_error) {
    if (errno)
      fprintf(stderr, "%s: %s\n", strerror(errno), filename);
    free(fi);
    exit(EXIT_FAILURE);
  }
  return fi;
}
void find_closest_flight(int requested_departure, int *departure_time, int *arrival_time)
{
  struct file_info *flights =  load_data(FILE_PATH);
  int diff;
  size_t f;
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
  for (f = 0; f < flights->size; f++)  {
    diff = abs(requested_departure - flights->data[f][0]);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      *departure_time = flights->data[f][0];
      *arrival_time   = flights->data[f][1];
    }
  }
  free(flights);
}
