#include "rray.h"

sexp* rray_broadcast(sexp* x, sexp* dims) {
  int n_protect = 0;

  sexp* x_dims = KEEP_N(rray_dims(x), n_protect);

  const int* p_x = r_int_deref(x);

  // TODO:
  // if (!rray_is_broadcastable(x_dims, to_dims)) {
  //   stop_not_broadcastable(x_dims, to_dims);
  // }

  const r_ssize out_elements = rray_elements_from_dims(dims);
  const r_ssize out_dimensionality = r_length(dims);

  x_dims = KEEP_N(rray_dims_expand(x_dims, out_dimensionality), n_protect);

  sexp* out = KEEP_N(r_new_int(out_elements), n_protect);
  int* p_out = r_int_deref(out);

  int* p_out_dims = r_int_deref(dims);

  STEPPER_UNARY_INIT(x_dims, out_dimensionality, n_protect);

  for (r_ssize i = 0; i < out_elements; ++i) {
    r_ssize x_loc;

    STEPPER_UNARY_SYNC(x_loc);

    p_out[i] = p_x[x_loc];

    STEPPER_UNARY_NEXT(out_dimensionality, p_out_dims);
  }

  r_poke_dims(out, dims);

  FREE(n_protect);
  return out;
}
