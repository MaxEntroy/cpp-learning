#ifndef LOG_H_
#include <zlog/zlog.h>

#define DEBUG   0
#define INFO    1
#define NOTICE  2
#define WARN    3
#define ERROR   4
#define FATAL   5

typedef zlog_category_t *pzlog;
typedef int LogLevel;

pzlog LOG_INIT(const char* conf, const char* cat);
void LOG(pzlog c, LogLevel level, const char* log_msg);
void LOG_FINI();

#endif
