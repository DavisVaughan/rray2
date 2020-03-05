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

    if (axis >= 0) {
      continue;
    }

    // `NA` or negative
    if (axis == r_na_int) {
      r_abort("A missing `axes` value was found at location %td.", i + 1);
    } else {
      r_abort("A negative `axes` value was found at location %td.", i + 1);
    }
  }

  FREE(1);
  return axes;
}
