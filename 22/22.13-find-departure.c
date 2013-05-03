#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define DATA_ERROR(f, l, s) fprintf(stderr, "Invalid data  %s:%ld  '%s'\n", (f), (l), (s))
#define TIME_STR_SIZE 6
#define FILE_PATH "data/flights.dat"

struct file_info {
  size_t size;
  int data[][2];
};
void print_am_pm(int minutes_since_midnight);
void find_closest_flight(int requested, int *departure_time, int *arrival_time);
int get_valid_input(void);
int to_minutes(char *);
bool is_format_valid(char *);
void convert(char *, int *, int *);
struct file_info *load_data(char *);

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
