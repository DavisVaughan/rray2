#include "rray.h"

struct rray_stepper new_stepper(sexp* dims) {
  r_ssize dimensionality = r_length(dims);

  sexp* array_loc = KEEP(r_new_int(dimensionality));
  int* p_array_loc = r_int_deref(array_loc);
  memset(p_array_loc, 0, dimensionality * sizeof(int));

  sexp* strides = KEEP(rray_strides_from_dims(dims));
  const r_ssize* p_strides = rray_strides_const_deref(strides);

  const int* p_dims = r_int_deref(dims);

  sexp* broadcastable = KEEP(r_new_raw(dimensionality * sizeof(bool)));
  bool* p_broadcastable = (bool*) r_raw_deref(broadcastable);

  for (r_ssize i = 0; i < dimensionality; ++i) {
    p_broadcastable[i] = (p_dims[i] == 1);
  }

  struct rray_stepper stepper = {
    .loc = 0,
    .array_loc = array_loc,
    .p_array_loc = p_array_loc,
    .broadcastable = broadcastable,
    .p_broadcastable = p_broadcastable,
    .strides = strides,
    .p_strides = p_strides,
    .dimensionality = dimensionality,
    .outdated = false
  };

  FREE(3);
  return stepper;
}
