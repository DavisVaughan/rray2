#ifndef RRAY_INTERNAL_VEC_DBL_H
#define RRAY_INTERNAL_VEC_DBL_H


#include "zzz-internal-r.h"


static inline sexp* r_scalar_dbl(double x) {
  return Rf_ScalarReal(x);
}


#endif
