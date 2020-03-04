#ifndef RRAY_EXPORTED_H
#define RRAY_EXPORTED_H


#include "internal.h"

// dimensionality.c
sexp* export_rray_dimensionality(sexp* x);

// dimensions.c
sexp* export_rray_dims(sexp* x);
sexp* export_rray_dims2(sexp* x, sexp* y);
sexp* export_rray_dims_common(sexp* dims, sexp* absent, sexp* env);
sexp* export_rray_dims_expand(sexp* dims, sexp* dimensionality);

// elements.c
sexp* export_rray_elements(sexp* x);
sexp* export_rray_elements_from_dims(sexp* dims);

// library.c
sexp* export_rray_init_library();

#endif
