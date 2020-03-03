#ifndef RRAY_VEC_H
#define RRAY_VEC_H


#include "zzz-internal-r.h"

static inline sexp* r_scalar_int(int x) {
  return Rf_ScalarInteger(x);
}


#endif
