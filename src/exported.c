#include "rray.h"
#include "library.h"
#include "exported.h"

// dimensionality.c

sexp* export_rray_dimensionality(sexp* x) {
  return r_scalar_int(rray_dimensionality(x));
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

  sexp* out = rray_dims_common(xs, dims, absent);

  FREE(3);
  return out;
}

// library.c

sexp* export_rray_init_library() {
  rray_init_library();
  return r_null;
}
