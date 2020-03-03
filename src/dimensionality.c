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
