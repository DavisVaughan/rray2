#include "rray.h"

sexp* rray_as_axes(sexp* axes, r_ssize dimensionality) {
  axes = KEEP(vec_cast(axes, rray_shared_empty_int));

  // TODO to remove duplicates!
  // axes = KEEP(vec_unique(axes));

  const r_ssize size = r_length(axes);
  const int* p_axes = r_int_deref(axes);

  for (r_ssize i = 0; i < size; ++i) {
    const int axis = p_axes[i];

    if (axis > dimensionality) {
      r_abort(
        "`axes` attempts to select axis %i, which is greater than the dimensionality, %td.",
        axis,
        dimensionality
      );
    }

    if (axis > 0) {
      continue;
    }

    // `NA`, negative, or zero
    if (axis == r_na_int) {
      r_abort("A missing `axes` value was found at location %td.", i + 1);
    } else if (axis == 0) {
      r_abort("A zero `axes` value was found at location %td.", i + 1);
    } else {
      r_abort("A negative `axes` value was found at location %td.", i + 1);
    }
  }

  FREE(1);
  return axes;
}

// -----------------------------------------------------------------------------

sexp* rray_axes_complement(sexp* axes, r_ssize dimensionality) {
  const r_ssize axes_dimensionality = r_length(axes);
  const r_ssize out_dimensionality = dimensionality - axes_dimensionality;

  const int* p_axes = r_int_deref(axes);

  sexp* out = KEEP(r_new_int(out_dimensionality));
  int* p_out = r_int_deref(out);

  r_ssize out_loc = 0;

  for (r_ssize i = 0; i < dimensionality; ++i) {
    const r_ssize axis = i + 1;
    bool seen = false;

    for (r_ssize j = 0; j < axes_dimensionality; ++j) {
      if (axis != p_axes[j]) {
        continue;
      }

      seen = true;
      break;
    }

    if (seen) {
      continue;
    }

    p_out[out_loc] = axis;
    ++out_loc;
  }

  FREE(1);
  return out;
}
