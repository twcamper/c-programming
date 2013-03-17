/* Thanks to Eric Radman, bitbucket.org/eradman/tdd-in-c  */
#include <stdio.h>

int tests_run = 0;
int assertions = 0;

#define _assert(e)            \
        do {                  \
          if (!(e)) {         \
            printf("%s:%u (%s) failed assertion:\v(%s)\n", __FILE__, __LINE__, __func__, #e);  \
            return 1;         \
          } else {            \
            assertions++;     \
          }                   \
        } while (0)

#define _run(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

static int all_tests(void);

int main(void) {
	int result = all_tests();
	if (result == 0)
		printf("PASSED\n");
	printf("Tests: %d\nAssertions: %d\n\n", tests_run, assertions);

	return result != 0;
}
