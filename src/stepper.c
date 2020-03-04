#include "rray.h"

struct rray_stepper new_stepper(sexp* dims) {
  r_ssize dimensionality = r_length(dims);

  sexp* loc_dims = KEEP(r_new_int(dimensionality));
  int* p_loc_dims = r_int_deref(loc_dims);
  memset(p_loc_dims, 0, dimensionality * sizeof(int));

  sexp* strides = KEEP(rray_strides_from_dims(dims));
  const double* p_strides = r_dbl_deref(strides);

  const int* p_dims = r_int_deref(dims);

  sexp* broadcastable = KEEP(r_new_raw(dimensionality * sizeof(bool)));
  bool* p_broadcastable = (bool*) r_raw_deref(broadcastable);

  for (r_ssize i = 0; i < dimensionality; ++i) {
    p_broadcastable[i] = (p_dims[i] == 1);
  }

  struct rray_stepper stepper = {
    .loc = 0,
    .loc_dims = loc_dims,
    .p_loc_dims = p_loc_dims,
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

void stepper_step(struct rray_stepper* p_stepper, r_ssize axis, r_ssize n) {
  const r_ssize dimensionality = p_stepper->dimensionality;

  if (axis >= dimensionality) {
    return;
  }

  const bool* p_broadcastable = p_stepper->p_broadcastable;

  if (p_broadcastable[axis]) {
    return;
  }

  p_stepper->p_loc_dims[axis] += n;
  p_stepper->outdated = true;
}

void stepper_reset(struct rray_stepper* p_stepper, r_ssize axis) {
  const r_ssize dimensionality = p_stepper->dimensionality;

  if (axis >= dimensionality) {
    return;
  }

  const bool* p_broadcastable = p_stepper->p_broadcastable;

  if (p_broadcastable[axis]) {
    return;
  }

  p_stepper->p_loc_dims[axis] = 0;
  p_stepper->outdated = true;
}

void stepper_loc(struct rray_stepper* p_stepper) {
  if (!p_stepper->outdated) {
    return;
  }

  r_ssize loc = 0;

  r_ssize dimensionality = p_stepper->dimensionality;
  const int* p_loc_dims = p_stepper->p_loc_dims;
  const double* p_strides = p_stepper->p_strides;

  for (r_ssize i = 0; i < dimensionality; ++i) {
    r_ssize stride = (r_ssize) p_strides[i];
    int loc_dim = p_loc_dims[i];

    loc += loc_dim * stride;
  }

  p_stepper->loc = loc;
  p_stepper->outdated = false;
}
