#include "rray.h"

// dimensionality.c

sexp* export_rray_dimensionality(sexp* x) {
  return r_scalar_int(rray_dimensionality(x));
}

// library.c

sexp* export_rray_init_library() {
  rray_init_library();
  return r_null;
}
