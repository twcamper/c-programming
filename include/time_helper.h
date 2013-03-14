#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#if !defined(_TIME_H) && !defined(_TIME_H_)
  #include <time.h>
#endif


#if !defined(_STDLIB_H) && !defined(_STDLIB_H_)
  #include <stdlib.h>
#endif

time_t random_time(void);
struct tm *random_tm(void);
#endif
