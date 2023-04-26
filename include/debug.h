#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <libgen.h>

#define __DEBUG_MODE__


#ifdef assert
#undef assert
#endif
#ifdef panic
#undef panic
#endif
#ifdef panic_on
#undef panic_on
#endif

#ifdef __DEBUG_MODE__

// extern FILE* debug_log;
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define Log(format,...) \
  fprintf(stderr, "[%s,%d,%s] " format "\n", \
      __FILENAME__, __LINE__, __func__, ## __VA_ARGS__)


#endif

#endif