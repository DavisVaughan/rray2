#ifndef RRAY_INTERNAL_VEC_CHR_H
#define RRAY_INTERNAL_VEC_CHR_H


#include "zzz-internal-r.h"

#define r_string_unwrap CHAR

static inline sexp** r_chr_deref(sexp* x) {
  return STRING_PTR(x);
}

static inline sexp* r_chr_get(sexp* x, r_ssize i) {
  return r_chr_deref(x)[i];
}

static inline const char* r_chr_get_c_string(sexp* x, r_ssize i) {
  return r_string_unwrap(r_chr_get(x, i));
}


#endif
