#include "rray.h"
#include "library.h"
#include "exported.h"

// arithmetic.c

sexp* export_rray_add(sexp* x, sexp* y) {
  return rray_add(x, y);
}

// axes.c

sexp* export_rray_as_axes(sexp* axes, sexp* dimensionality) {
  r_ssize dimensionality_ = rray_as_dimensionality(dimensionality);
  return rray_as_axes(axes, dimensionality_);
}

// broadcast.c

sexp* export_rray_broadcast(sexp* x, sexp* dims) {
  dims = KEEP(rray_as_dims(dims, r_c_arg_dims));

  sexp* out = rray_broadcast(x, dims);

  FREE(1);
  return out;
}

// dimensionality.c

sexp* export_rray_dimensionality(sexp* x) {
  return r_scalar_int(rray_dimensionality(x));
}

sexp* export_rray_as_dimensionality(sexp* dimensionality) {
  r_ssize dimensionality_ = rray_as_dimensionality(dimensionality);
  return r_length_as_scalar_int(dimensionality_);
}

// dimensions.c

sexp* export_rray_dims(sexp* x) {
  return rray_dims(x);
}

sexp* export_rray_dims2(sexp* x, sexp* y) {
  return rray_dims2(x, y);
}

sexp* export_rray_dims_common(sexp* dims, sexp* absent, sexp* env) {
  sexp* xs = KEEP(rlang_env_dots_list(env));

  if (dims != r_null) {
    dims = rray_as_dims(dims, r_c_arg_dot_dims);
  }
  KEEP(dims);

  absent = KEEP(vec_cast(absent, rray_shared_empty_int));

  if (r_length(absent) == 0) {
    r_abort("`.absent` must not be length 0.");
  }

  sexp* out = rray_dims_common(xs, dims, absent);

  FREE(3);
  return out;
}

sexp* export_rray_dims_expand(sexp* dims, sexp* dimensionality) {
  dims = KEEP(rray_as_dims(dims, r_c_arg_dims));
  r_ssize dimensionality_ = rray_as_dimensionality(dimensionality);

  sexp* out = rray_dims_expand(dims, dimensionality_);

  FREE(1);
  return out;
}

sexp* export_rray_dims_split(sexp* dims, sexp* axes) {
  dims = KEEP(rray_as_dims(dims, r_c_arg_dims));

  r_ssize dimensionality = r_length(dims);
  axes = KEEP(rray_as_axes(axes, dimensionality));

  sexp* out = rray_dims_split(dims, axes);

  FREE(2);
  return out;
}

sexp* export_rray_as_dims(sexp* dims, sexp* dims_arg) {
  const char* dims_arg_ = rray_as_arg(dims_arg, r_c_arg_dims_arg);
  return rray_as_dims(dims, dims_arg_);
}

// elements.c

sexp* export_rray_elements(sexp* x) {
  return r_length_as_scalar_dbl(rray_elements(x));
}

sexp* export_rray_elements_from_dims(sexp* dims) {
  dims = KEEP(rray_as_dims(dims, r_c_arg_dims));

  r_ssize elements = rray_elements_from_dims(dims);
  sexp* out = r_length_as_scalar_dbl(elements);

  FREE(1);
  return out;
}

// library.c

sexp* export_rray_init_library() {
  rray_init_library();
  return r_null;
}

// strides.c

sexp* export_rray_strides(sexp* x) {
  return rray_strides(x);
}

sexp* export_rray_strides_from_dims(sexp* dims) {
  dims = KEEP(rray_as_dims(dims, r_c_arg_dims));

  sexp* out = rray_strides_from_dims(dims);

  FREE(1);
  return out;
}
