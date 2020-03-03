#include "zzz-internal-r.h"
#include "zzz-internal-util.h"
#include "zzz-internal-type.h"
#include <stdio.h>
#include <stdarg.h>

#include "zzz-internal-cnd.h"


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


void r_stop_scalar_type(sexp* x, const char* arg) {
  if (arg) {
    r_abort("`%s` must be a vector, not %s.", arg, r_sexp_as_friendly_c_string(x));
  } else {
    r_abort("Input must be a vector, not %s.", r_sexp_as_friendly_c_string(x));
  }

  never_reached("stop_scalar_type");
}


#undef BUFSIZE
#undef INTERP
