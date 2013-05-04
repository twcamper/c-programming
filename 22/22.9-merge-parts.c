#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #include <sys/types.h>  /* for off_t */
#endif
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "error.h"
#include "part-type.h"

typedef struct file_info {
  char *name;
  off_t size;
  size_t count;
} FileInfo;

/*
 * This is an Absolute DOG of an algorithm!!
 *
 * Reading and writing single records at a time KILLS it in performance.
 *
 * At 100k records per file:
 * 
 * this:
 * real4m50.708s user4m49.040s sys0m1.007s
 *
 * single record read/write:
 * real0m0.150s  user0m0.023s  sys0m0.063s
 */
static void validate_input_file(char *f, struct stat *fs, size_t record_size)
{
  if (stat(f, fs) !=0)
    exit_error(__FILE__, f);

  if (fs->st_size == 0 || fs->st_size % record_size) {
    fprintf(stderr, "Empty or corrupt file '%s': size must be multiple of %ld\n",
        f,
        (size_t)record_size);
    exit(EXIT_FAILURE);
  }
}
static void  sort_input_files(
    char *f1, struct stat *fs1,
    char *f2, struct stat *fs2,
    FileInfo *larger,
    FileInfo *smaller,
    off_t record_size)
{
  if (fs1->st_size > fs2->st_size) {
    larger->name = f1;
    larger->size = fs1->st_size;
    smaller->name = f2;
    smaller->size = fs2->st_size;
  } else {
    larger->name = f2;
    larger->size = fs2->st_size;
    smaller->name = f1;
    smaller->size = fs1->st_size;
  }
  larger->count = larger->size / record_size;
  smaller->count = smaller->size / record_size;
}
static int read_input(FileInfo *f, Part buffer, size_t record_size)
{
  FILE *stream;
  if ((stream = fopen(f->name, "rb")) == NULL) {
    print_error(__FILE__, f->name);
    return -1;;
  }
  bool read_failure = false;
  if ((fread(buffer, record_size, f->count, stream) < f->count) || ferror(stream)) {
    print_error(__FILE__, f->name);
    errno = 0;
    read_failure = true;
  }
  if ((fclose(stream) == EOF) || read_failure) {
    if (errno)
      print_error(__FILE__, f->name);
    return -1;
  }
  return 0;
}
static int write_output(char *output_filename, Part out_buffer, size_t out_count, size_t record_size)
{
  FILE *ostream;
  if ((ostream = fopen(output_filename, "wb")) == NULL) {
    print_error(__FILE__, output_filename);
    return -1;
  }
  bool write_error = false;
  if (fwrite(out_buffer, record_size, out_count, ostream) < out_count || ferror(ostream)) {
    write_error = true;
    print_error(__FILE__, output_filename);
  }
  if (fclose(ostream) == EOF || write_error) {
    print_error(__FILE__, output_filename);
    return -1;
  }
  return 0;
}
static size_t merge_buffers(Part in_buffer, size_t in_count, Part out_buffer, size_t out_count)
{
  size_t o, m;
  for (size_t i = 0; i < in_count; i++) {
    o = 0;
    while ( o < out_count && out_buffer[o].number < in_buffer[i].number) o++;
    if (out_buffer[o].number == in_buffer[i].number) {
      if (strcmp(out_buffer[o].name, in_buffer[i].name) != 0) {
        fprintf(stderr, "Part #%d: name conflict\t \"%s\" vs. \"%s\"\n",
            out_buffer[o].number,
            out_buffer[o].name,
            in_buffer[i].name);
        continue;
      }
      if (!change_part_on_hand(&out_buffer[o], in_buffer[i].on_hand)) {
        fprintf(stderr, "Invalid new quantity on hand for Part #%d\n", out_buffer[o].number);
      }
    } else {
      for (m = out_count; m > o; m--)
        out_buffer[m] = out_buffer[m-1];
      out_buffer[o] = in_buffer[i];
      out_count++;
    }
  }
  return out_count;
}
int main(int argc, char *argv[])
{
  if (argc != 4)
    invocation_error(argv[0], "[input file 1] [input file 2] [output file]"); 

  char *output_filename = argv[3];
  struct stat file1_stat, file2_stat;
  FileInfo larger, smaller;
  off_t record_size = (off_t)get_part_record_size();

  validate_input_file(argv[1], &file1_stat, record_size);
  validate_input_file(argv[2], &file2_stat, record_size);

  sort_input_files(argv[1], &file1_stat, argv[2], &file2_stat, &larger, &smaller, record_size);

  Part out_buffer = (Part)malloc(larger.size + smaller.size);
  if (!out_buffer)
    memory_error(__FILE__, __LINE__, __func__);

  if (read_input(&larger, out_buffer, record_size) != 0) {
    free(out_buffer);
    exit(EXIT_FAILURE);
  }

  Part in_buffer = malloc(smaller.size);
  if (!in_buffer) {
    free(out_buffer);
    memory_error(__FILE__, __LINE__, __func__);
  }

  if (read_input(&smaller, in_buffer, record_size) != 0) {
    free(in_buffer);
    free(out_buffer);
    exit(EXIT_FAILURE);
  }

  size_t out_count = merge_buffers(in_buffer, smaller.count, out_buffer, larger.count);
  free(in_buffer);

  if (write_output(output_filename, out_buffer, out_count, record_size) != 0) {
    free(out_buffer);
    exit(EXIT_FAILURE);
  }

  free(out_buffer);
  return 0;
}
