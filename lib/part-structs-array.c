#include "parts.h"
#include "part-type.h"
#define INITIAL_SIZE 30

struct parts_type {
  size_t count;
  struct part_type *rows;
  size_t requested_row_allocation;
};

Parts new_db(size_t initial_size)
{
  Parts db = malloc(sizeof(struct parts_type));
  if (db == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  db->count = 0;
  db->requested_row_allocation = initial_size;
  db->rows = malloc(db->requested_row_allocation * sizeof(struct part_type));

  if (db->rows == NULL)
    memory_error(__FILE__, __LINE__, __func__);

  return db;
}
#define CHECKSUM_LEN  MD5_DIGEST_LENGTH * 2
char *checksum(Parts db)
{
  int i, b;
  unsigned char md5[MD5_DIGEST_LENGTH]; 
  static char md5_string[CHECKSUM_LEN];
  MD5((unsigned char *)db->rows, db->count * sizeof(db->rows[0]), md5);

  for (b = 0, i = 0; i < CHECKSUM_LEN; b++, i +=2 )
    sprintf(md5_string + i, "%.2x", (int)*(md5 + b));

  return md5_string;
}
void destroy_db(Parts db)
{
  free(db->rows);
  free(db);
}
size_t size(Parts db)
{
  return db->count;
}
static int resize_db(Parts db)
{
  db->requested_row_allocation *= 2;
  struct part_type *temp = realloc(db->rows, db->requested_row_allocation * sizeof(db->rows[0]));
  if (temp == NULL)
    return -1;

  db->rows = temp;
  return 0;
}
int delete_part(Parts db, PartNumber number)
{
  size_t i;

  for (i = 0; i < db->count; i++)
    if (get_part_number(&db->rows[i]) == number)
      break;

  /* not found */
  if (i == db->count)
    return -1;

  for (;i < db->count; i++)
    db->rows[i] = db->rows[i + 1];

  db->count--;
  return 0;
}
int insert_part(Parts db, Part p)
{
  size_t i, j;

  if (db->count == db->requested_row_allocation)
    if (resize_db(db) != 0) {
      return -1;
    }
  /* invalid record? */
  if (!p)
    return -3;

  /* find position to insert new record */
  for (i = 0; i < db->count && get_part_number(&db->rows[i]) <= get_part_number(p); i++)
    if (get_part_number(&db->rows[i]) == get_part_number(p))
      return -2;  /* duplicate record */

  /* shift remaining records down by 1 */
  for (j = db->count; j > i; j--)
    db->rows[j] = db->rows[j-1];
  /* insert our new record in the newly vacant hole */
  db->rows[i] = *p;  /* copy from the object pointed to */
  destroy_part(p);   /* then free it, since we can't maintain the pointer info */
  db->count++;
  return 0;
}
/**********************************************************
 * find_part: Looks up a part number in the inventory     *
 *            array. Returns the array index if the part  *
 *            number is found; otherwise, returns -1.     *
 **********************************************************/
Part find_part(Parts db, PartNumber part_number)
{
  size_t i;
  for (i = 0; i < db->count; i++)
    if (get_part_number(&db->rows[i]) == part_number)
      return &db->rows[i];
  return NULL;
}
void iterate(Parts db, void (*op)(Part p))
{
  for (size_t i = 0; i < db->count; i++) {
    op(&db->rows[i]);
  }
}
Part approximate_part(Parts db, PartNumber part_number)
{
  size_t i = 0;
  PartNumber pn;

  if (db->count == 0)
    return NULL;

  /* return first if the target is smaller than all */
  if (get_part_number(&db->rows[0]) > part_number)
    return &db->rows[0];

  /* find whichever the exact part or the next greatest */
  while ( i < db->count && (pn = get_part_number(&db->rows[i])) < part_number)
     ++i;
  /* return the exact part or the next smallest */
  return &db->rows[(pn == part_number ? i : i - 1)];
}

static int write_db(char *filename, Parts db, char *write_mode)
{
  FILE *ostream;
  size_t n_written = 0;
  if ((ostream = fopen(filename, write_mode)) == NULL) {
    print_error(errno, __FILE__, filename);
    return -1;
  }

  n_written = fwrite(db->rows, sizeof(db->rows[0]), db->count, ostream);
  if (n_written < db->count || ferror(ostream))
    return -2;

  if (fclose(ostream) == EOF)
    return -3;

  return 0;
}
/* write contents to file, which is overwritten if it existed */
int dump(char *outfile, Parts db)
{
  return write_db(outfile, db, "wb");
}
/* append contents to file and reset count to 0 */
int flush_to_disk(char *file, Parts db)
{
  int rc = 0;
  if ((rc = write_db(file, db, "ab")) == 0)
    db->count = 0;

  return rc;
}
Parts restore(char *infile)
{
  FILE *istream;
  size_t n_read = 0;
  if ((istream = fopen(infile, "rb")) == NULL) {
    print_error(errno, __FILE__, infile);
    return NULL;
  }

  struct stat infile_stat;
  if (stat(infile, &infile_stat) != 0) {
    print_error(errno, __FILE__, infile);
    return NULL;
  }
  off_t record_size = (off_t)sizeof(struct part_type);
  if (infile_stat.st_size % record_size) {
    fprintf(stderr, "Corrupt file '%s': size must be multiple of %ld\n",
        infile,
        sizeof(struct part_type));
    return NULL;
  }
  Parts db = new_db((infile_stat.st_size / record_size));

  n_read = fread( db->rows, sizeof(db->rows[0]), db->requested_row_allocation, istream);
  if (n_read < db->requested_row_allocation) {
    print_error(errno, __FILE__, infile);
    destroy_db(db);
    return NULL;
  }
  db->count = n_read;

  if (fclose(istream) == EOF) {
    destroy_db(db);
    return NULL;
  }

  return db;
}
