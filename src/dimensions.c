#include "rray.h"

sexp* rray_dims_impl(sexp* x) {
  // When reducing, this is used as a signal to choose the other dims value
  if (x == r_null) {
    return r_null;
  }

  switch (r_typeof(x)) {
  case r_type_logical:
  case r_type_integer:
  case r_type_double:
  case r_type_character:
  case r_type_raw:
  case r_type_complex:
  case r_type_list:
    break;
  default:
    r_stop_scalar_type(x, "x");
  }

  sexp* dims = r_get_dims(x);

  if (dims == r_null) {
    r_ssize length = r_length(x);
    return r_length_as_scalar_int(length);
  }

  return dims;
}

sexp* rray_dims(sexp* x) {
  // For invariants to hold, `NULL` returns dimensions of `0`
  if (x == r_null) {
    return rray_shared_zero_int;
  }

  return rray_dims_impl(x);
}

// -----------------------------------------------------------------------------

static sexp* rray_dims2_impl(sexp* x_dims, sexp* y_dims) {
  if (x_dims == r_null) {
    return y_dims;
  }
  if (y_dims == r_null) {
    return x_dims;
  }

  int* p_x_dims = r_int_deref(x_dims);
  int* p_y_dims = r_int_deref(y_dims);

  r_ssize x_dimensionality = r_length(x_dims);
  r_ssize y_dimensionality = r_length(y_dims);

  r_ssize dimensionality = rray_dimensionality2(x_dimensionality, y_dimensionality);

  sexp* out = KEEP(r_new_int(dimensionality));
  int* p_out = r_int_deref(out);

  for (r_ssize i = 0; i < dimensionality; ++i) {
    if (i >= x_dimensionality) {
      p_out[i] = p_y_dims[i];
    } else if (i >= y_dimensionality) {
      p_out[i] = p_x_dims[i];
    } else {
      p_out[i] = rray_axis2(i + 1, p_x_dims[i], p_y_dims[i]);
    }
  }

  FREE(1);
  return out;
}

sexp* rray_dims2(sexp* x, sexp* y) {
  sexp* x_dims = KEEP(rray_dims(x));
  sexp* y_dims = KEEP(rray_dims(y));

  sexp* out = rray_dims2_impl(x_dims, y_dims);

  FREE(2);
  return out;
}

// -----------------------------------------------------------------------------

/*
 * @param xs A list of objects to compute the common dimensions for.
 * @param dims An integer vector of dimensions to start the common computation
 *   with, or `NULL` to only use dimensions from `xs`.
 * @param absent An integer vector of dimensions to use when `xs` is an empty
 *   list and no `dims` is provided.
 */
sexp* rray_dims_common(sexp* xs, sexp* dims, sexp* absent) {
  r_ssize size = r_length(xs);

  xs = KEEP(r_shallow_duplicate(xs));

  for (r_ssize i = 0; i < size; ++i) {
    sexp* x = r_list_get(xs, i);
    r_list_set(xs, i, rray_dims_impl(x));
  }

  dims = KEEP(reduce(dims, xs, &rray_dims2_impl));

  if (dims == r_null) {
    dims = absent;
  }

  FREE(2);
  return dims;
}

// -----------------------------------------------------------------------------

sexp* rray_dims_expand(sexp* dims, r_ssize dimensionality) {
  r_ssize dims_dimensionality = r_length(dims);

  if (dims_dimensionality == dimensionality) {
    return dims;
  }

  if (dims_dimensionality > dimensionality) {
    r_abort("Cannot reduce dimensionality from %td to %td", dims_dimensionality, dimensionality);
  }

  sexp* out = KEEP(r_new_int(dimensionality));
  int* p_out = r_int_deref(out);

  const int* p_dims = r_int_deref(dims);

  r_ssize i = 0;

  for (; i < dims_dimensionality; ++i) {
    p_out[i] = p_dims[i];
  }

  for (; i < dimensionality; ++i) {
    p_out[i] = 1;
  }

  FREE(1);
  return out;
}

// -----------------------------------------------------------------------------

sexp* rray_as_dims(sexp* dims) {
  dims = KEEP(vec_cast(dims, rray_shared_empty_int));

  r_ssize size = r_length(dims);

  if (size == 0) {
    r_abort("`dims` must have a length of at least 1, not 0.");
  }

  const int* p_dims = r_int_deref(dims);

  for (r_ssize i = 0; i < size; ++i) {
    const int dim = p_dims[i];

    if (dim >= 0) {
      continue;
    }

    if (dim == r_na_int) {
      r_abort("A missing `dims` value was found at location %td.", i + 1);
    } else {
      r_abort("A negative `dims` value was found at location %td.", i + 1);
    }
  }

  FREE(1);
  return dims;
}
