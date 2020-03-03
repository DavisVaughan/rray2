#ifndef RRAY_INTERNAL_VEC_H
#define RRAY_INTERNAL_VEC_H


#include "zzz-internal-r.h"
#include "zzz-internal-type.h"


static inline sexp* r_new_vec(enum r_type type, r_ssize length) {
  return Rf_allocVector(type, length);
}


#endif
