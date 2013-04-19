#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define BYTE_OFFSET_INIT 8
#define CHAR_OFFSET_INT  39
#define LINE_LENGTH 50

static void print_e(int e, char *program, char *file)
{
  fprintf(stderr, "%s: %s: %s\n", program, file, strerror(e));
}
static void print_line(char *line)
{
  /* sprintf leaves terminators mid-line, so clear them out so we can print the full line */
  for (int i = BYTE_OFFSET_INIT; i < CHAR_OFFSET_INT; i++)
    if (line[i] == '\0')
      line[i] = ' ';
  printf("%s\n", line);
}

int main(int argc, char *argv[])
{
  char header[2][LINE_LENGTH] = {
    "Offset              Bytes              Characters",
    "______  _____________________________  __________" };
  char line[LINE_LENGTH + 1] = {' '};

  int ch;
  int character = 0;
  int line_offset = 0;
  int byte_offset = BYTE_OFFSET_INIT, char_offset = CHAR_OFFSET_INT;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [file]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  FILE *fp = fopen(argv[1], "rb");
  if (!fp) {
    print_e(errno, argv[0], argv[1]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", header[0]);
  printf("%s\n", header[1]);

  while ((ch = fgetc(fp)) != EOF) {
    if (character == 0) {
      sprintf(line, "%6d  ", line_offset);
      line_offset += 10;
    }
    sprintf(line + byte_offset, "%02X ", ch);
    sprintf(line + char_offset, "%c", isprint(ch) ? ch : '.');
    character++;
    char_offset++;
    byte_offset += 3;

    if (character == 10) {
      print_line(line);
      character = 0;
      char_offset = CHAR_OFFSET_INT;
      byte_offset = BYTE_OFFSET_INIT;
    }
  }
  if (ferror(fp)) {
    print_e(errno, argv[0], argv[1]);
    exit(EXIT_FAILURE);
  }

  if (character > 0)
    print_line(line);

  if (fclose(fp) == EOF) {
    print_e(errno, argv[0], argv[1]);
    exit(EXIT_FAILURE);
  }
  return 0;
}
