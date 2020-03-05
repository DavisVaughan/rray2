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
  dims = KEEP(vec_cast(dims, rray_shared_empty_int));

  if (r_int_any_na_or_negative(dims)) {
    r_abort("`dims` must not contain `NA` values and cannot be negative.");
  }

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

  dims = KEEP(vec_cast(dims, rray_shared_empty_int));
  absent = KEEP(vec_cast(absent, rray_shared_empty_int));

  if (dims != r_null && r_length(dims) == 0) {
    r_abort("`.dims` must not be length 0.");
  }

  if (r_length(absent) == 0) {
    r_abort("`.absent` must not be length 0.");
  }

  sexp* out = rray_dims_common(xs, dims, absent);

  FREE(3);
  return out;
}

sexp* export_rray_dims_expand(sexp* dims, sexp* dimensionality) {
  dims = KEEP(vec_cast(dims, rray_shared_empty_int));
  dimensionality = KEEP(vec_cast(dimensionality, rray_shared_empty_int));

  if (r_length(dimensionality) != 1) {
    r_abort("`dimensionality` must be length 1, not %td", r_length(dimensionality));
  }

  r_ssize dimensionality_ = r_int_get(dimensionality, 0);

  sexp* out = rray_dims_expand(dims, dimensionality_);

  FREE(2);
  return out;
}

sexp* export_rray_as_dims(sexp* dims) {
  return rray_as_dims(dims);
}

// elements.c

sexp* export_rray_elements(sexp* x) {
  return r_length_as_scalar_dbl(rray_elements(x));
}

sexp* export_rray_elements_from_dims(sexp* dims) {
  dims = KEEP(vec_cast(dims, rray_shared_empty_int));

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
  dims = KEEP(vec_cast(dims, rray_shared_empty_int));

  if (r_int_any_na_or_negative(dims)) {
    r_abort("`dims` must not contain `NA` values and cannot be negative.");
  }

  sexp* out = rray_strides_from_dims(dims);

  FREE(1);
  return out;
}
