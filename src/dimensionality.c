#include "rray.h"

r_ssize rray_dimensionality(sexp* x) {
  if (x == r_null) {
    return 1;
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
    return 1;
  }

  return r_length(dims);
}

r_ssize rray_dimensionality2(r_ssize x_dimensionality, r_ssize y_dimensionality) {
  if (x_dimensionality > y_dimensionality) {
    return x_dimensionality;
  } else {
    return y_dimensionality;
  }
}

// -----------------------------------------------------------------------------

r_ssize rray_as_dimensionality(sexp* dimensionality) {
  dimensionality = KEEP(vec_cast(dimensionality, rray_shared_empty_int));

  if (r_length(dimensionality) != 1) {
    r_abort("`dimensionality` must be length 1, not %td.", r_length(dimensionality));
  }

  r_ssize out = r_int_get(dimensionality, 0);

  if (out < 0) {
    if (out == r_na_int) {
      r_abort("`dimensionality` cannot be `NA`.");
    } else {
      r_abort("`dimensionality` cannot be negative.");
    }
  }

  FREE(1);
  return out;
}
