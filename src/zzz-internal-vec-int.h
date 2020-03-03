#ifndef RRAY_INTERNAL_VEC_INT_H
#define RRAY_INTERNAL_VEC_INT_H


#include "zzz-internal-r.h"
#include "zzz-internal-type.h"
#include "zzz-internal-vec.h"


static inline sexp* r_scalar_int(int x) {
  return Rf_ScalarInteger(x);
}


static inline sexp* r_new_int(r_ssize length) {
  return r_new_vec(r_type_integer, length);
}

static inline int* r_int_deref(sexp* x) {
  return INTEGER(x);
}


extern sexp* rray_shared_empty_int;
extern sexp* rray_shared_zero_int;


#endif
