#include "rray.h"

sexp* rray_strides(sexp* x) {
  sexp* dims = KEEP(rray_dims(x));

  sexp* out = rray_strides_from_dims(dims);

  FREE(1);
  return out;
}

// It is possible that the dims could be integers, but the strides could
// overflow into long vector range, so we always return a "strides" vector.
// This is a raw vector backed by an r_ssize array.
sexp* rray_strides_from_dims(sexp* dims) {
  r_ssize dimensionality = r_length(dims);
  int* p_dims = r_int_deref(dims);

  sexp* out = KEEP(rray_new_strides(dimensionality));
  r_ssize* p_out = rray_strides_deref(out);

  r_ssize stride = 1;

  for (r_ssize i = 0; i < dimensionality; ++i) {
    p_out[i] = stride;
    stride *= (r_ssize) p_dims[i];
  }

  FREE(1);
  return out;
}

sexp* rray_strides_as_double(sexp* strides) {
  const r_ssize* p_strides = rray_strides_const_deref(strides);

  r_ssize size = rray_strides_length(strides);

  sexp* out = KEEP(r_new_dbl(size));
  double* p_out = r_dbl_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    p_out[i] = (double) p_strides[i];
  }

  FREE(1);
  return out;
}
