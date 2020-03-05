#include "rray.h"

r_ssize rray_array_loc_as_flat_loc(const int* p_array_loc,
                                   const r_ssize* p_strides,
                                   const r_ssize dimensionality) {
  r_ssize loc = 0;

  for (r_ssize i = 0; i < dimensionality; ++i) {
    r_ssize stride = p_strides[i];
    int axis_loc = p_array_loc[i];

    loc += axis_loc * stride;
  }

  return loc;
}
