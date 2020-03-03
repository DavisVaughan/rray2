#include "rray.h"

// Compile with `-fvisibility=hidden -DHAVE_VISIBILITY_ATTRIBUTE`
// if you link to this library
#include <R_ext/Visibility.h>
#define export attribute_visible extern

// -----------------------------------------------------------------------------

// dimensionality.c
sexp* export_rray_dimensionality(sexp* x);

// library.c
extern sexp* export_rray_init_library();

static const r_callable r_callables[] = {
  {"export_rray_dimensionality", (r_fn_ptr) &export_rray_dimensionality, 1},
  {"export_rray_init_library",   (r_fn_ptr) &export_rray_init_library, 0},
  {NULL, NULL, 0}
};

// -----------------------------------------------------------------------------

static const r_external externals[] = {
  {NULL, NULL, 0}
};

// -----------------------------------------------------------------------------

export void R_init_rray2(r_dll_info* dll) {
  r_register_r_callables(dll, r_callables, externals);
}
