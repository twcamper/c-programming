#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "parts.h"
#include "part.h"
#include "inventory-view.h"
#include "tokenize.h"

#define NOUN_FILE "data/nouns.txt"
#define NOUN_MAX   3000
#define NOUN_BYTES 18000
#define ADJ_FILE "data/adjectives.txt"
#define ADJ_MAX    1000
#define ADJ_BYTES  6000

static void print_line(Part p)
{
  static size_t i = 0;
  printf("%9ld: %-11d       %-25s   %-11d       %-d\n",
         ++i,
         get_part_number(p),
         get_part_name(p),
         get_part_on_hand(p),
         get_part_price(p));
}
static size_t jagged_sequence(size_t previous)
{
  return previous + (rand() % 13) + 1;
}
static char *random_part_name(char *n[], size_t n_count, char *a[], size_t a_count)
{
  static char name[NAME_LEN + 1]; /* static so we can return it */
  snprintf(name, NAME_LEN + 1, "%s, %s %s",
      n[(rand() % n_count-1)],
      a[(rand() % a_count-1)],
      a[(rand() % a_count-1)]);

  name[0] = toupper(name[0]);
  return name;
}
static PartQuantity random_part_quantity(void)
{
  return rand() % (INT_MAX / 8);
}

static PartPrice random_part_price(void)
{
  return rand() % (INT_MAX / 20);
}
static size_t get_word_pointers(char **tokens, char *filename, char *content, size_t byte_max)
{
  FILE *fp;
  size_t n_read = 0;
  if ((fp = fopen(filename, "rb")) == NULL)
    exit_error(errno, __FILE__, filename);

  if (!(n_read = fread(content, sizeof(content[0]), byte_max, fp)))
    if (ferror(fp) || feof(fp))
      exit_error(errno, __FILE__, "fread()");

  if (fclose(fp) == EOF)
    exit_error(errno, __FILE__, filename);

  return tokenize(content, tokens);
}
int main(int argc, char *argv[])
{
  if (argc != 3)
    invocation_error(argv[0], "[output file] [size]");

  char *output_file = argv[1];
  size_t records = atol(argv[2]);
  size_t i, part_number, noun_count, adj_count;
  char *nouns[NOUN_MAX], noun_file_content[NOUN_BYTES];
  char *adjectives[ADJ_MAX], adj_file_content[ADJ_BYTES];
  int rc;

  Parts db = new_db(records);

  noun_count = get_word_pointers(nouns, NOUN_FILE, noun_file_content, NOUN_BYTES);
  adj_count = get_word_pointers(adjectives, ADJ_FILE, adj_file_content, ADJ_BYTES);

  srand((unsigned int) time(NULL));
  for (part_number = 0, i = 0; i < records; i++) {
    part_number = jagged_sequence(part_number);
    rc = insert_part(db, set_part(part_number,
          random_part_name(nouns, noun_count, adjectives, adj_count),
          random_part_quantity(),
          random_part_price()));
    if (rc) {
      fprintf(stderr, "%s: %d  insert_part() failed: return code %d on iteration %ld\n",
          __FILE__, __LINE__, rc, i);
      destroy_db(db);
      exit(EXIT_FAILURE);
    }
  }

  iterate(db, print_line);

  if (dump(output_file, db) != 0) {
    destroy_db(db);
    exit_error(errno, argv[0], output_file);
  }
  destroy_db(db);

  return 0;
}
