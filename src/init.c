#include "export.h"
#include "exported.h"

// -----------------------------------------------------------------------------

static const r_callable r_callables[] = {
  {"export_rray_dimensionality",           (r_fn_ptr) &export_rray_dimensionality, 1},
  {"export_rray_dims",                     (r_fn_ptr) &export_rray_dims, 1},
  {"export_rray_dims2",                    (r_fn_ptr) &export_rray_dims2, 2},
  {"export_rray_dims_common",              (r_fn_ptr) &export_rray_dims_common, 3},
  {"export_rray_elements",                 (r_fn_ptr) &export_rray_elements, 1},
  {"export_rray_elements_from_dims",       (r_fn_ptr) &export_rray_elements_from_dims, 1},
  {"export_rray_init_library",             (r_fn_ptr) &export_rray_init_library, 0},
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
