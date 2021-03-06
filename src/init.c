#include "export.h"
#include "exported.h"

// -----------------------------------------------------------------------------

static const r_callable r_callables[] = {
  // arithmetic.c
  {"export_rray_add",                      (r_fn_ptr) &export_rray_add, 2},

  // axes.c
  {"export_rray_as_axes",                  (r_fn_ptr) &export_rray_as_axes, 2},
  {"export_rray_axes_complement",          (r_fn_ptr) &export_rray_axes_complement, 2},

  // broadcast.c
  {"export_rray_broadcast",                (r_fn_ptr) &export_rray_broadcast, 2},

  // dimensionality.c
  {"export_rray_dimensionality",           (r_fn_ptr) &export_rray_dimensionality, 1},
  {"export_rray_as_dimensionality",        (r_fn_ptr) &export_rray_as_dimensionality, 1},

  // dimensions.c
  {"export_rray_dims",                     (r_fn_ptr) &export_rray_dims, 1},
  {"export_rray_dims2",                    (r_fn_ptr) &export_rray_dims2, 2},
  {"export_rray_dims_common",              (r_fn_ptr) &export_rray_dims_common, 3},
  {"export_rray_dims_expand",              (r_fn_ptr) &export_rray_dims_expand, 2},
  {"export_rray_dims_split",               (r_fn_ptr) &export_rray_dims_split, 2},
  {"export_rray_dims_select",              (r_fn_ptr) &export_rray_dims_select, 2},
  {"export_rray_dims_reduce",              (r_fn_ptr) &export_rray_dims_reduce, 2},
  {"export_rray_as_dims",                  (r_fn_ptr) &export_rray_as_dims, 2},

  // elements.c
  {"export_rray_elements",                 (r_fn_ptr) &export_rray_elements, 1},
  {"export_rray_elements_from_dims",       (r_fn_ptr) &export_rray_elements_from_dims, 1},

  // library.c
  {"export_rray_init_library",             (r_fn_ptr) &export_rray_init_library, 0},

  // strides.c
  {"export_rray_strides",                  (r_fn_ptr) &export_rray_strides, 2},
  {"export_rray_strides_from_dims",        (r_fn_ptr) &export_rray_strides_from_dims, 2},

  // reducer.c
  {"export_rray_sum",                      (r_fn_ptr) &export_rray_sum, 2},

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
