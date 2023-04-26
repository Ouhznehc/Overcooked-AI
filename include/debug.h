#ifndef __DEBUG_H__
#define __DEBUG_H__

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

#define Log(format, ...) \
    printf( "[%s:%d %s] " format, "\n", \
        basename(__FILE__), __LINE__, __func__, ## __VA_ARGS__)


#endif

#endif