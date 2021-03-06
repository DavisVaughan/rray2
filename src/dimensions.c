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

static inline r_ssize rray_axis2(r_ssize axis, r_ssize x_dim, r_ssize y_dim) {
  if (x_dim == y_dim) {
    return x_dim;
  } else if (x_dim == 1) {
    return y_dim;
  } else if (y_dim == 1) {
    return x_dim;
  } else {
    r_abort("Dimensions along axis %td cannot be broadcast: %td, %td.", axis, x_dim, y_dim);
  }
}

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

/*
 * Split `dims` into a list of size two. The first element of the list holds
 * the dims specified by `axes`, the second element of the list holds the
 * remaining dims. Dims are split in the order specified by `axes`.
 */
sexp* rray_dims_split(sexp* dims, sexp* axes) {
  sexp* out = KEEP(r_new_list(2));

  const r_ssize dimensionality = r_length(dims);

  const r_ssize axes_dims_size = r_length(axes);
  const r_ssize non_axes_dims_size = dimensionality - axes_dims_size;

  sexp* axes_dims = KEEP(r_new_int(axes_dims_size));
  sexp* non_axes_dims = KEEP(r_new_int(non_axes_dims_size));

  int* p_axes_dims = r_int_deref(axes_dims);
  int* p_non_axes_dims = r_int_deref(non_axes_dims);

  const int* p_dims = r_int_deref(dims);
  const int* p_axes = r_int_deref(axes);

  int non_axes_dims_loc = 0;

  for (r_ssize i = 0; i < dimensionality; ++i) {
    const int axis = i + 1;
    bool seen = false;

    for (r_ssize j = 0; j < axes_dims_size; ++j) {
      if (axis != p_axes[j]) {
        continue;
      }

      p_axes_dims[j] = p_dims[i];
      seen = true;
      break;
    }

    if (seen) {
      continue;
    }

    p_non_axes_dims[non_axes_dims_loc] = p_dims[i];
    ++non_axes_dims_loc;
  }

  r_list_set(out, 0, axes_dims);
  r_list_set(out, 1, non_axes_dims);

  FREE(3);
  return out;
}

// -----------------------------------------------------------------------------

sexp* rray_dims_select(sexp* dims, sexp* axes) {
  const int* p_dims = r_int_deref(dims);
  const int* p_axes = r_int_deref(axes);

  const r_ssize size = r_length(axes);

  sexp* out = KEEP(r_new_int(size));
  int* p_out = r_int_deref(out);

  for (r_ssize i = 0; i < size; ++i) {
    p_out[i] = p_dims[p_axes[i] - 1];
  }

  FREE(1);
  return out;
}

// -----------------------------------------------------------------------------

sexp* rray_dims_reduce(sexp* dims, sexp* axes) {
  const int* p_dims = r_int_deref(dims);
  const int* p_axes = r_int_deref(axes);

  const r_ssize dims_size = r_length(dims);
  const r_ssize axes_size = r_length(axes);

  sexp* out = KEEP(r_new_int(dims_size));
  int* p_out = r_int_deref(out);

  // Initialize with `dims`
  for (r_ssize i = 0; i < dims_size; ++i) {
    p_out[i] = p_dims[i];
  }

  // Reduce `axes` locations to 1
  for (r_ssize i = 0; i < axes_size; ++i) {
    p_out[p_axes[i] - 1] = 1;
  }

  FREE(1);
  return out;
}

// -----------------------------------------------------------------------------

sexp* rray_as_dims(sexp* dims, const char* dims_arg) {
  dims = KEEP(vec_cast(dims, rray_shared_empty_int));

  r_ssize size = r_length(dims);

  if (size == 0) {
    r_abort("`%s` must have a length of at least 1, not 0.", dims_arg);
  }

  const int* p_dims = r_int_deref(dims);

  for (r_ssize i = 0; i < size; ++i) {
    const int dim = p_dims[i];

    if (dim >= 0) {
      continue;
    }

    if (dim == r_na_int) {
      r_abort("A missing `%s` value was found at location %td.", dims_arg, i + 1);
    } else {
      r_abort("A negative `%s` value was found at location %td.", dims_arg, i + 1);
    }
  }

  FREE(1);
  return dims;
}
