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

void stepper_step(struct rray_stepper* p_stepper, r_ssize axis, r_ssize n) {
  const r_ssize dimensionality = p_stepper->dimensionality;

  if (axis >= dimensionality) {
    return;
  }

  const bool* p_broadcastable = p_stepper->p_broadcastable;

  if (p_broadcastable[axis]) {
    return;
  }

  p_stepper->p_array_loc[axis] += n;
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

  p_stepper->p_array_loc[axis] = 0;
  p_stepper->outdated = true;
}

void stepper_sync(struct rray_stepper* p_stepper) {
  if (!p_stepper->outdated) {
    return;
  }

  const r_ssize dimensionality = p_stepper->dimensionality;
  const int* p_array_loc = p_stepper->p_array_loc;
  const r_ssize* p_strides = p_stepper->p_strides;

  p_stepper->loc = rray_array_loc_as_flat_loc(
    p_array_loc,
    p_strides,
    dimensionality
  );

  p_stepper->outdated = false;
}
