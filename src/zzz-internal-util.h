#ifndef RRAY_UTIL_H
#define RRAY_UTIL_H


#include "zzz-internal-r.h"

__attribute__((noreturn)) inline void never_reached(const char* fn) {
  Rf_errorcall(r_null, "Internal error: Reached the unreachable in `%s()`.", fn);
}

#endif
