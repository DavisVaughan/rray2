#include "rray.h"

sexp* rray_add(sexp* x, sexp* y) {
  int n_protect = 0;

  const int* p_x = r_int_deref(x);
  const int* p_y = r_int_deref(y);

  sexp* x_dims = KEEP_N(rray_dims(x), n_protect);
  sexp* y_dims = KEEP_N(rray_dims(y), n_protect);

  sexp* out_dims = KEEP_N(rray_dims2(x, y), n_protect);
  int* p_out_dims = r_int_deref(out_dims);

  const r_ssize out_elements = rray_elements_from_dims(out_dims);
  const r_ssize out_dimensionality = r_length(out_dims);

  sexp* out = KEEP_N(r_new_int(out_elements), n_protect);
  int* p_out = r_int_deref(out);

  STEPPER_BINARY_INIT(x_dims, y_dims, out_dimensionality, n_protect);

  for (r_ssize i = 0; i < out_elements; ++i) {
    r_ssize x_loc;
    r_ssize y_loc;

    STEPPER_BINARY_SYNC(x_loc, y_loc);

    // "Do something"
    p_out[i] = p_x[x_loc] + p_y[y_loc];

    STEPPER_BINARY_NEXT(out_dimensionality, p_out_dims);
  }

  r_poke_dims(out, out_dims);

  FREE(n_protect);
  return out;
}
