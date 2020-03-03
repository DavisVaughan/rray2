#include "zzz-internal-cnd.h"
#include "zzz-internal-util.h"
#include "zzz-internal-r.h"
#include <stdio.h>
#include <stdarg.h>


#define BUFSIZE 8192

#define INTERP(BUF, FMT, DOTS) {      \
  va_list dots;                       \
  va_start(dots, FMT);                \
  vsnprintf(BUF, BUFSIZE, FMT, dots); \
  va_end(dots);                       \
                                      \
  BUF[BUFSIZE - 1] = '\0';            \
}


void r_abort(const char* fmt, ...) {
  char buf[BUFSIZE];
  INTERP(buf, fmt, ...);

  Rf_errorcall(R_NilValue, buf);

  never_reached("r_abort");
}



#undef BUFSIZE
#undef INTERP
