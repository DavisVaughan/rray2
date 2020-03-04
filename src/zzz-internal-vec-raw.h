#ifndef RRAY_INTERNAL_VEC_RAW_H
#define RRAY_INTERNAL_VEC_RAW_H


#include "zzz-internal-r.h"
#include "zzz-internal-type.h"
#include "zzz-internal-vec.h"


static inline sexp* r_new_raw(r_ssize length) {
  return r_new_vec(r_type_raw, length);
}

static inline r_byte_t* r_raw_deref(sexp* x) {
  return RAW(x);
}

#endif
