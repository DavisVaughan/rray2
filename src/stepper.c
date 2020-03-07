#include "rray.h"

struct rray_stepper new_stepper(sexp* dims) {
  const r_ssize dimensionality = r_length(dims);

  sexp* strides = KEEP(rray_strides_from_dims(dims));
  const r_ssize* p_strides = rray_strides_const_deref(strides);

  const int* p_dims = r_int_deref(dims);

  struct rray_stepper stepper = {
    .loc = 0,
    .dims = dims,
    .p_dims = p_dims,
    .strides = strides,
    .p_strides = p_strides
  };

  FREE(1);
  return stepper;
}
