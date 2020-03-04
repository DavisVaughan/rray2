#include "rray.h"

r_ssize rray_elements(sexp* x) {
  switch (r_typeof(x)) {
  case r_type_null:
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

  return r_length(x);
}

r_ssize rray_elements_from_dims(sexp* dims) {
  r_ssize out = 1;

  r_ssize dimensionality = r_length(dims);
  int* p_dims = r_int_deref(dims);

  // TODO: Maybe check for ptrdiff_t overflow? Would be very hard to actually
  // overflow here since each axis has to be an integer.
  for (r_ssize i = 0; i < dimensionality; ++i) {
    int dim = p_dims[i];

    if (dim == r_na_int) {
      r_abort("`dims` cannot contain `NA`");
    }

    out *= (r_ssize) dim;
  }

  return out;
}
