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

  if (dims != r_null) {
    // TODO: `vec_cast(dims, rray_shared_empty_integer)`
    if (r_typeof(dims) != r_type_integer) {
      r_abort("`.dims` must be an integer vector.");
    }
  }

  // TODO `vec_cast(absent, rray_shared_empty_integer)`
  if (r_typeof(absent) != r_type_integer) {
    r_abort("`.absent` must be an integer vector.");
  }

  sexp* out = rray_dims_common(xs, dims, absent);

  FREE(1);
  return out;
}

// library.c

sexp* export_rray_init_library() {
  rray_init_library();
  return r_null;
}
