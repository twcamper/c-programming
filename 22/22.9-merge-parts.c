#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
#include <sys/types.h>  /* for off_t */
#endif
#include <stdio.h>
#include <sys/stat.h>
#include "error.h"
#include "part-type.h"

int main(int argc, char *argv[])
{
  if (argc != 4)
    invocation_error(argv[0], "[input file 1] [input file 2] [output file]"); 

  char *larger_filename, *smaller_filename, *output_filename = argv[3];
  struct stat file1_stat, file2_stat;
  off_t record_size = (off_t)get_part_record_size();
  off_t smaller_size;
  size_t larger_count, smaller_count;

  if (stat(argv[1], &file1_stat) != 0)
    exit_error(errno, argv[0], argv[1]);

  if (file1_stat.st_size % record_size)
    fprintf(stderr, "Corrupt file '%s': size must be multiple of %ld\n",
        argv[1],
        (size_t)record_size);

  if (stat(argv[2], &file2_stat) != 0)
    exit_error(errno, argv[0], argv[2]);

  if (file2_stat.st_size % record_size)
    fprintf(stderr, "Corrupt file '%s': size must be multiple of %ld\n",
        argv[2],
        (size_t)record_size);

  if (file1_stat.st_size > file2_stat.st_size) {
    larger_filename = argv[1];
    smaller_filename = argv[2];
    smaller_size = file2_stat.st_size;
    larger_count = file1_stat.st_size / record_size;
    smaller_count = file2_stat.st_size / record_size;
  } else {
    larger_filename = argv[2];
    smaller_filename = argv[1];
    smaller_size = file1_stat.st_size;
    larger_count = file2_stat.st_size / record_size;
    smaller_count = file1_stat.st_size / record_size;
  }

  size_t combined_size = (size_t) file1_stat.st_size + file2_stat.st_size;
  Part merge_buffer = (Part)malloc(combined_size);
  if (!merge_buffer)
    memory_error(__FILE__, __LINE__, __func__);

  Part other_buffer = malloc(smaller_size);
  if (!other_buffer)
    memory_error(__FILE__, __LINE__, __func__);

  FILE *larger_stream, *smaller_stream;

  if ((larger_stream = fopen(larger_filename, "rb")) == NULL) {
    exit_error(errno,argv[0], larger_filename);
  }

  if ((smaller_stream = fopen(smaller_filename, "rb")) == NULL) {
    if (fclose(larger_stream) == EOF)
      print_error(errno, __FILE__, larger_filename);
    exit_error(errno,argv[0], smaller_filename);
  }

  if (fread(merge_buffer, record_size, larger_count, larger_stream) < larger_count) {
    print_error(errno, argv[0], larger_filename);
    if (fclose(larger_stream) == EOF)
      print_error(errno, __FILE__, larger_filename);
    if (fclose(smaller_stream) == EOF)
      print_error(errno, __FILE__, smaller_filename);
    exit(EXIT_FAILURE);
  }
  if (fread(other_buffer, record_size, smaller_count, smaller_stream) < smaller_count) {
    print_error(errno, argv[0], smaller_filename);
    if (fclose(larger_stream) == EOF)
      print_error(errno, __FILE__, larger_filename);
    if (fclose(smaller_stream) == EOF)
      print_error(errno, __FILE__, smaller_filename);
    exit(EXIT_FAILURE);
  }
  if (fclose(larger_stream) == EOF)
    print_error(errno, __FILE__, larger_filename);
  if (fclose(smaller_stream) == EOF)
    exit_error(errno, __FILE__, smaller_filename);


  for (size_t s = 0; s < smaller_count; s++) {
    for (size_t l = 0; l < larger_count; l++) {
      if ((merge_buffer + l)->number == (other_buffer + s)->number) {
        if (strcmp((merge_buffer + l)->name, (other_buffer + s)->name) != 0) {
          fprintf(stderr, "Part #%d: name conflict\n", (merge_buffer + l)->number);
          continue;
        }
        if (!set_part_on_hand((merge_buffer + l), (other_buffer + s)->on_hand)) {
          fprintf(stderr, "Invalid new quantity on hand for Part #%d\n", (merge_buffer + l)->number);
          continue;
        }
      }
    }
  }

  /*
   * for each record in the smaller
   *   check each part number in the larger until:
   *      same number is found:
   *        if name values differ
   *          report to stderr
   *          continue
   *        combine in stock values
   *        if the new value is invalid
   *          report to stderr
   *          continue
   *      larger part number is found:
   *        increment "added" counter
   *        shift all subsequent elements in the larger buffer
   *        copy record from smaller into the hole
   *      we reach the end without finding a larger part number
   *        increment "added" counter
   *        copy record from smaller at end
   *
   * open the output file
   * fwrite the output buffer
   * close the output file
   */


  return 0;
}
