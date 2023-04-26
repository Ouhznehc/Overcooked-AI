#ifndef __DEBUG_H__
#define __DEBUG_H__

#define __DEBUG_MODE__






#ifdef __DEBUG_MODE__

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define Log(format,...) \
      fprintf(stderr, "[%s, %d, %s] " format "\n", \
          __FILENAME__, __LINE__, __func__, ## __VA_ARGS__)

#define panic(format, ...) \
      do { \
        Log("panic: " format, ## __VA_ARGS__); \
        exit(1); \
      } while (0)

#define Assert(cond,format,...) \
      do{ \
        if(!(cond)) { \
          panic(format); \
        }  \
      }while(0)

#define TODO() panic("please implement me")


#else
#define Log(format,...)
#define panic(format, ...)
#define Assert(cond,format,...)
#define TODO()
#endif

#endif