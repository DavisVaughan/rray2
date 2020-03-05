#ifndef RRAY_EXPORTED_H
#define RRAY_EXPORTED_H


#include "internal.h"

// arithmetic.c
sexp* export_rray_add(sexp* x, sexp* y);

// axes.c
sexp* export_rray_as_axes(sexp* axes, sexp* dimensionality);

// broadcast.c
sexp* export_rray_broadcast(sexp* x, sexp* dims);

// dimensionality.c
sexp* export_rray_dimensionality(sexp* x);
sexp* export_rray_as_dimensionality(sexp* dimensionality);

// dimensions.c
sexp* export_rray_dims(sexp* x);
sexp* export_rray_dims2(sexp* x, sexp* y);
sexp* export_rray_dims_common(sexp* dims, sexp* absent, sexp* env);
sexp* export_rray_dims_expand(sexp* dims, sexp* dimensionality);
sexp* export_rray_dims_split(sexp* dims, sexp* axes);
sexp* export_rray_as_dims(sexp* dims, sexp* dims_arg);

// elements.c
sexp* export_rray_elements(sexp* x);
sexp* export_rray_elements_from_dims(sexp* dims);

// library.c
sexp* export_rray_init_library();

// strides.c
sexp* export_rray_strides(sexp* x);
sexp* export_rray_strides_from_dims(sexp* dims);

#endif
