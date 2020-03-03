#include "rray.h"

sexp* rray_dims(sexp* x) {
  if (x == r_null) {
    return r_scalar_int(0);
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
    return r_length_to_scalar_int(length);
  }

  return dims;
}
