#ifndef RRAY_INTERNAL_VEC_LIST_H
#define RRAY_INTERNAL_VEC_LIST_H


#include "zzz-internal-r.h"
#include "zzz-internal-type.h"
#include "zzz-internal-vec.h"


static inline sexp* r_new_list(r_ssize length) {
  return r_new_vec(r_type_list, length);
}

static inline sexp* r_list_get(sexp* x, r_ssize i) {
  return VECTOR_ELT(x, i);
}
static inline void r_list_set(sexp* x, r_ssize i, sexp* value) {
  SET_VECTOR_ELT(x, i, value);
}


#endif
