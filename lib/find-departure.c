#include "find-departure.h"

#define LINE_SIZE  (TIME_STR_SIZE * 2 + 2)

typedef struct file_info {
  size_t size;
  int data[][2];
} FileInfo;
static bool is_file_valid(char *f)
{
  struct stat fs;
  stat(f, &fs);

  if (fs.st_size < LINE_SIZE) {
    fprintf(stderr, "Empty or corrupt file: %s\n", f);
    return false;
  }
  return true;
}

static FileInfo *load_data(char *filename)
{
  FILE *fp;
  char line[LINE_SIZE];
  char d[TIME_STR_SIZE], a[TIME_STR_SIZE];
  int m;
  bool read_error = false, data_error = false;
  FileInfo *fi = NULL;  /* NULL so first realloc is just like malloc() */
  size_t l;

  if (!is_file_valid(filename))
    exit(EXIT_FAILURE);

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "failed to open %s\n", filename);
    exit(EXIT_FAILURE);
  }
  for (l = 0;fgets(line, sizeof(line), fp) != NULL; l++)
  {
    if (!(fi = realloc(fi, sizeof(FileInfo) + (sizeof(int (*)[2])) *  (l + 1)))) {
      fprintf(stderr, "realloc: %s:%d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    }
    sscanf(line, "%s %s", d, a);

    if ((m = to_minutes(d)) == -1) {
      DATA_ERROR(filename, l + 1, d);
      break;
    }
    fi->data[l][0] = m;
    if ((m = to_minutes(a)) == -1) {
      DATA_ERROR(filename, l + 1, a);
      break;
    }
    fi->data[l][1] = m;
  }
  fi->size = l;

  if (!feof(fp) || ferror(fp)) {
    if (!data_error)  {
      perror(FILE_PATH);
      read_error = true;
      errno = 0;
    }
  }

  if (fclose(fp) == EOF || read_error || data_error) {
    if (!data_error && !read_error)
      perror(filename);
    free(fi);
    exit(EXIT_FAILURE);
  }
  return fi;
}
static void overnight_search(FileInfo *flights, int requested_departure, int *departure, int *arrival)
{

  /* adjust first flight in the morning to be
   * a number 'larger than midnight' to
   * simplify the comparison.
   */
  int morning_departure = flights->data[0][0] + (24*60);
  int night_deaparture  = flights->data[flights->size - 1][0];
  if (requested_departure < flights->data[0][0])
    requested_departure += 24*60;

  *departure = flights->data[0][0];
  *arrival   = flights->data[0][1];
  if (abs(requested_departure - night_deaparture) < abs(requested_departure - morning_departure)) {
    *departure = night_deaparture;
    *arrival   = flights->data[flights->size - 1][1];
  }
}
static void single_day_search(FileInfo *flights, int requested_departure, int *departure, int *arrival)
{
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
  int diff, minimum_difference = 23*60+59;
  size_t f;
  for (f = 0; f < flights->size; f++)  {
    diff = abs(requested_departure - flights->data[f][0]);
    if (diff < minimum_difference)  {
      minimum_difference = diff;
      *departure = flights->data[f][0];
      *arrival   = flights->data[f][1];
    }
  }
}
void find_closest_flight(int requested_departure, int *departure_time, int *arrival_time)
{
  FileInfo *flights =  load_data(FILE_PATH);
  if (requested_departure < flights->data[0][0] || requested_departure > flights->data[flights->size -1][0])
    overnight_search(flights, requested_departure, departure_time, arrival_time);
  else
    single_day_search(flights, requested_departure, departure_time, arrival_time);
  free(flights);
}
