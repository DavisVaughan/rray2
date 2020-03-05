#ifndef RRAY_LOCATION_H
#define RRAY_LOCATION_H


#include "internal.h"

r_ssize rray_array_loc_as_flat_loc(const int* p_array_loc,
                                   const r_ssize* p_strides,
                                   const r_ssize dimensionality);


#endif
