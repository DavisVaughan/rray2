#include "rray.h"

sexp* rray_sum(sexp* x, sexp* axes) {
  const int* p_x = r_int_deref(x);

  sexp* x_dims = KEEP(rray_dims(x));
  const int* p_x_dims = r_int_deref(x_dims);

  const r_ssize x_dimensionality = r_length(x_dims);

  sexp* x_strides = KEEP(rray_strides_from_dims(x_dims));
  const r_ssize* p_x_strides = rray_strides_const_deref(x_strides);

  sexp* x_array_loc = KEEP(r_new_int(x_dimensionality));
  int* p_x_array_loc = r_int_deref(x_array_loc);
  memset(p_x_array_loc, 0, x_dimensionality * sizeof(int));

  const int* p_axes = r_int_deref(axes);

  sexp* non_axes = KEEP(rray_axes_complement(axes, x_dimensionality));
  const int* p_non_axes = r_int_deref(non_axes);

  sexp* axes_dims = KEEP(rray_dims_select(x_dims, axes));
  const int* p_axes_dims = r_int_deref(axes_dims);

  sexp* non_axes_dims = KEEP(rray_dims_select(x_dims, non_axes));
  const int* p_non_axes_dims = r_int_deref(non_axes_dims);

  const r_ssize axes_dims_elements = rray_elements_from_dims(axes_dims);
  const r_ssize non_axes_dims_elements = rray_elements_from_dims(non_axes_dims);

  const r_ssize axes_dimensionality = r_length(axes_dims);
  const r_ssize non_axes_dimensionality = r_length(non_axes_dims);

  sexp* out = KEEP(r_new_dbl(non_axes_dims_elements));
  double* p_out = r_dbl_deref(out);

  r_ssize x_loc = 0;

  for (r_ssize i = 0; i < non_axes_dims_elements; ++i) {
    double elt_out = 0;

    for (r_ssize j = 0; j < axes_dims_elements; ++j) {
      elt_out += (double) p_x[x_loc];

      for (r_ssize k = 0; k < axes_dimensionality; ++k) {
        const int axis = p_axes[k] - 1;
        const r_ssize x_axis_stride = p_x_strides[axis];
        const int x_axis_dim = p_x_dims[axis];

        ++p_x_array_loc[axis];
        x_loc += x_axis_stride;

        if (p_x_array_loc[axis] < x_axis_dim) {
          break;
        }

        p_x_array_loc[axis] = 0;
        x_loc -= x_axis_stride * x_axis_dim;
      }
    }

    p_out[i] = elt_out;

    for (r_ssize k = 0; k < non_axes_dimensionality; ++k) {
      const int axis = p_non_axes[k] - 1;
      const r_ssize x_axis_stride = p_x_strides[axis];
      const int x_axis_dim = p_x_dims[axis];

      ++p_x_array_loc[axis];
      x_loc += x_axis_stride;

      if (p_x_array_loc[axis] < x_axis_dim) {
        break;
      }

      p_x_array_loc[axis] = 0;
      x_loc -= x_axis_stride * x_axis_dim;
    }
  }

  sexp* out_dims = KEEP(rray_dims_reduce(x_dims, axes));

  r_poke_dims(out, out_dims);

  FREE(8);
  return out;
}
