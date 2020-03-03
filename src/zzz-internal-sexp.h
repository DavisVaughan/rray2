#ifndef RRAY_INTERNAL_SEXP_H
#define RRAY_INTERNAL_SEXP_H

#include "zzz-internal-r.h"
#include "zzz-internal-cnd.h"
#include "zzz-internal-vec-int.h"

static inline r_ssize r_length(sexp* x) {
  return Rf_xlength(x);
}

static inline sexp* r_length_to_scalar_int(r_ssize length) {
  if (length > R_SHORT_SSIZE_MAX) {
    r_abort("Object must have length less than %i, not %td.", R_SHORT_SSIZE_MAX, length);
  }

  return r_scalar_int(length);
}

#define r_mark_precious R_PreserveObject
#define r_unmark_precious R_ReleaseObject

static inline void r_mark_shared(sexp* x) {
  MARK_NOT_MUTABLE(x);
}

static inline bool r_is_object(sexp* x) {
  return OBJECT(x);
}

#endif
