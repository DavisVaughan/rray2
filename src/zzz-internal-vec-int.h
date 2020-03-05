#ifndef RRAY_INTERNAL_VEC_INT_H
#define RRAY_INTERNAL_VEC_INT_H


#include "zzz-internal-r.h"
#include "zzz-internal-sexp.h"
#include "zzz-internal-cnd.h"
#include "zzz-internal-type.h"
#include "zzz-internal-vec.h"

#define r_na_int NA_INTEGER

static inline sexp* r_scalar_int(int x) {
  return Rf_ScalarInteger(x);
}

static inline sexp* r_length_as_scalar_int(r_ssize length) {
  if (length > R_SHORT_SSIZE_MAX) {
    r_abort("Object must have length less than %i, not %td.", R_SHORT_SSIZE_MAX, length);
  }

  return r_scalar_int(length);
}


static inline sexp* r_new_int(r_ssize length) {
  return r_new_vec(r_type_integer, length);
}

static inline int* r_int_deref(sexp* x) {
  return INTEGER(x);
}

static inline int r_int_get(sexp* x, r_ssize i) {
  return r_int_deref(x)[i];
}

extern sexp* rray_shared_empty_int;
extern sexp* rray_shared_zero_int;


#endif
