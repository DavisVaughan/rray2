#include "rray.h"

r_ssize rray_dimensionality(sexp* x) {
  if (x == r_null) {
    return 0;
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
