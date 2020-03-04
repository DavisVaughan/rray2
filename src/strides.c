#include "rray.h"

sexp* rray_strides(sexp* x) {
  sexp* dims = KEEP(rray_dims(x));

  sexp* out = rray_strides_from_dims(dims);

  FREE(1);
  return out;
}

// It is possible that the dims could be integers, but the strides could
// overflow into long vector range, so we always return a double vector. It
// should always be able to be cast to a r_ssize.
sexp* rray_strides_from_dims(sexp* dims) {
  r_ssize dimensionality = r_length(dims);
  int* p_dims = r_int_deref(dims);

  sexp* out = KEEP(r_new_dbl(dimensionality));
  double* p_out = r_dbl_deref(out);

  double stride = 1;

  for (r_ssize i = 0; i < dimensionality; ++i) {
    p_out[i] = stride;
    stride *= (double) p_dims[i];
  }

  FREE(1);
  return out;
}
