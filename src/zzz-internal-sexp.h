#ifndef RRAY_INTERNAL_SEXP_H
#define RRAY_INTERNAL_SEXP_H

#include "zzz-internal-r.h"

static inline r_ssize r_length(sexp* x) {
  return Rf_xlength(x);
}

#define r_mark_precious R_PreserveObject
#define r_unmark_precious R_ReleaseObject

static inline void r_mark_shared(sexp* x) {
  MARK_NOT_MUTABLE(x);
}
static inline bool r_is_shared(sexp* x) {
  return MAYBE_SHARED(x);
}

static inline bool r_is_object(sexp* x) {
  return OBJECT(x);
}

static inline sexp* r_shallow_duplicate(sexp* x) {
  return Rf_shallow_duplicate(x);
}

static inline sexp* r_maybe_duplicate(sexp* x) {
  if (r_is_shared(x)) {
    return r_shallow_duplicate(x);
  } else {
    return x;
  }
}

#endif
