/* Thanks to Eric Radman, bitbucket.org/eradman/tdd-in-c  */
#include <stdio.h>

#define RED       "\033[0;36m"
#define GREEN     "\033[0;32m"
#define END_COLOR "\033[0m"
int tests_run = 0;
int assertions = 0;

#define _assert(e)            \
        do {                  \
          if (!(e)) {         \
            printf("%s%s:%u (%s) failed assertion:\v(%s)\n", RED, __FILE__, __LINE__, __func__, #e);  \
            return 1;         \
          } else {            \
            assertions++;     \
          }                   \
        } while (0)

#ifdef TEST_VERBOSE
  #define _run(test) do { printf("\t%s\n",  #test); int r=test(); tests_run++; if(r) return r; } while(0)
#else
  #define _run(test) do { int r=test(); tests_run++; if(r) return r; } while(0)
#endif

static int all_tests(void);

int main(int argc, char *argv[]) {
  if (argc < 0)
    puts("Would the compiler please shut up about unused argc?");

	int result = all_tests();
	if (result == 0)
		printf("%sPASS\t", GREEN);
  else
    printf("%sFAIL\t", RED);
	printf("Tests: %d\tAssertions: %d\t%s\n%s", tests_run, assertions, argv[0], END_COLOR);

	return result != 0;
}
