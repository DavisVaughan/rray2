#ifndef RRAY_STRIDES_H
#define RRAY_STRIDES_H


#include "internal.h"

static inline sexp* rray_new_strides(r_ssize length) {
  return r_new_raw(length * sizeof(r_ssize));
}

static inline r_ssize rray_strides_length(sexp* x) {
  return r_length(x) / sizeof(r_ssize);
}

static inline r_ssize* rray_strides_deref(sexp* x) {
  return (r_ssize*) r_raw_deref(x);
}

static inline const r_ssize* rray_strides_const_deref(sexp* x) {
  return (const r_ssize*) r_raw_deref(x);
}

sexp* rray_strides(sexp* x);
sexp* rray_strides_from_dims(sexp* dims);
sexp* rray_strides_as_double(sexp* strides);


#endif
