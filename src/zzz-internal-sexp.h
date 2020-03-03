#ifndef RRAY_INTERNAL_SEXP_H
#define RRAY_INTERNAL_SEXP_H

#include "zzz-internal-r.h"

static inline r_ssize r_length(sexp* x) {
  return Rf_xlength(x);
}

static inline void r_mark_shared(sexp* x) {
  MARK_NOT_MUTABLE(x);
}

static inline bool r_is_object(sexp* x) {
  return OBJECT(x);
}

#endif
