#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
    exit(EXIT_FAILURE);
  int mm, dd, yyyy;
  char *months[13] = {"INVALID",
                  "January", "February", "March",
                  "April", "May", "June",
                  "July", "August", "September",
                  "Octobre", "November", "December"};

  for (int i = 1; i < argc; i++) {
    sscanf(argv[i], "%2d%*[-/]%2d%*[-/]%4d", &mm, &dd, &yyyy);
    if (mm < 1 || mm > 12) {
      fprintf(stderr, "Invalid month: %d\n", mm);
      continue;
    }
    printf("%s %d, %4d\n", months[mm], dd, yyyy);
  }

  return 0;
}
