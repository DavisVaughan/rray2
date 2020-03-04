#ifndef RRAY_INTERNAL_VEC_DBL_H
#define RRAY_INTERNAL_VEC_DBL_H


#include "zzz-internal-r.h"
#include "zzz-internal-type.h"
#include "zzz-internal-vec.h"


static inline sexp* r_scalar_dbl(double x) {
  return Rf_ScalarReal(x);
}

static inline sexp* r_length_as_scalar_dbl(r_ssize length) {
  return r_scalar_dbl((double) length);
}

static inline sexp* r_new_dbl(r_ssize length) {
  return r_new_vec(r_type_double, length);
}

static inline double* r_dbl_deref(sexp* x) {
  return REAL(x);
}

#endif
