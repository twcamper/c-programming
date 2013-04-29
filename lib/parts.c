#include "parts.h"

void load(Parts db)
{
  insert_part(db, set_part(212, "Named Part, unlabled", 1, 100));
  insert_part(db, set_part(12, "Flex Wing Grooming Mower", 19, 1200));
  insert_part(db, set_part(400, "Grommet", 18, 01));
  insert_part(db, set_part(1, "Fern Spore sorter, gross", 100, 12300));
  insert_part(db, set_part(1024, "Health Meter, fin.", 30, 434200));
  insert_part(db, set_part(1989776, "Tractor Beam cowl", 30, 9990101));
  insert_part(db, set_part(98, "magneto", 11, 101));
  insert_part(db, set_part(50, "manual key sort plucker", 11, 89));
  insert_part(db, set_part(40, "Parts List Catalog Index", 19, 0));
  insert_part(db, set_part(99, "funnel lip, unfinished", 1010, 4344));
  insert_part(db, set_part(512, "caterpiller feet, left", 1010, 99));
  insert_part(db, set_part(101, "Mental Health Services", 40, 100));
  insert_part(db, set_part(2, "Gas Ring, Municipal", 18, 214798900));
  insert_part(db, set_part(30, "System flipper", 80, 1301));
  insert_part(db, set_part(35, "Stabilizers, horiz,(pair)", 90, 3000000));
  insert_part(db, set_part(97, "Sink, heat, fur", 2147483647, 123220));
  insert_part(db, set_part(401, "Tension Mount", 10, 1039));
  insert_part(db, set_part(3, "Gas Ring, Occipital", 10, 8995));
  insert_part(db, set_part(33, "System Rotator", 8, 1301));
  insert_part(db, set_part(53, "Stabilizers, vert,(pair)", 90, 280000));
  insert_part(db, set_part(3497, "Sink, burbling", 47, 12720));
}
Parts read_parts_file(char *infile, int(*process_records)(Parts, FILE *, off_t))
{
  FILE *istream;
  if ((istream = fopen(infile, "rb")) == NULL) {
    print_error(errno, __FILE__, infile);
    return NULL;
  }

  struct stat infile_stat;
  if (stat(infile, &infile_stat) != 0) {
    print_error(errno, __FILE__, infile);
    return NULL;
  }
  off_t record_size = (off_t)get_part_record_size();
  if (infile_stat.st_size % record_size) {
    fprintf(stderr, "Corrupt file '%s': size must be multiple of %ld\n",
        infile,
        (size_t)record_size);
    return NULL;
  }
  Parts db = new_db(infile_stat.st_size / record_size);
  if (process_records(db, istream, record_size) !=0)  {
    print_error(errno, __FILE__, infile);
    return NULL;
  }

  if (fclose(istream) == EOF) {
    print_error(errno, __FILE__, infile);
    return NULL;
  }

  return db;
}
int read_to_db(Parts db, FILE *fp, off_t record_size);
Parts load_parts(char *infile)
{
  return read_parts_file(infile, read_to_db);

}
int write_db(char *filename, Parts db, char *write_mode);
/* write contents to file, which is overwritten if it existed */
int dump(char *outfile, Parts db)
{
  return write_db(outfile, db, "wb");
}
