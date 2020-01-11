#include "log.h"

#include <stdio.h>
#include <stdlib.h>

pzlog LOG_INIT(const char* conf, const char* cat) {
  int ret = zlog_init(conf);
  if(ret) {
    fprintf(stderr, "%s", "zlog init failed");
    exit(EXIT_FAILURE);
  }

  pzlog c = zlog_get_category(cat);
  if(!c) {
    fprintf(stderr, "%s", "zlog get cat failed");
    zlog_fini();
    exit(EXIT_FAILURE);
  }

  return c;
}

void LOG(pzlog c, LogLevel level, const char* log_msg) {
  switch(level) {
    case DEBUG  : zlog_debug(c, "%s", log_msg);break;
    case INFO   : zlog_info(c, "%s", log_msg); break;
    case NOTICE : zlog_notice(c, "%s", log_msg); break;
    case WARN   : zlog_warn(c, "%s", log_msg); break;
    case ERROR  : zlog_error(c, "%s", log_msg); break;
    case FATAL  : zlog_fatal(c, "%s", log_msg); break;
    default     : zlog_error(c, "Undefined log level."); break;
  }
}

void LOG_FINI() {
  zlog_fini();
}
