#ifndef RRAY_INTERNAL_VEC_LGL_H
#define RRAY_INTERNAL_VEC_LGL_H


#include "zzz-internal-r.h"
#include "zzz-internal-sexp.h"
#include "zzz-internal-type.h"
#include "zzz-internal-cnd.h"

#define r_na_lgl NA_LOGICAL

static inline int* r_lgl_deref(sexp* x) {
  return LOGICAL(x);
}

static inline int r_lgl_get(sexp* x, r_ssize i) {
  return r_lgl_deref(x)[i];
}

static inline int r_scalar_lgl_get(sexp* x) {
  return r_lgl_get(x, 0);
}

static inline bool r_is_bool(sexp* x) {
  return
    r_typeof(x) == r_type_logical &&
    r_length(x) == 1 &&
    r_scalar_lgl_get(x) != NA_LOGICAL;
}

static inline bool r_as_bool(sexp* x, const char* arg) {
  if (!r_is_bool(x)) {
    r_abort("`%s` must be a single, logical, non-missing value.", arg);
  }

  return r_scalar_lgl_get(x);
}


#endif
