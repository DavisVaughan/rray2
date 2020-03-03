#ifndef RRAY_EXPORTED_H
#define RRAY_EXPORTED_H


#include "internal.h"

// dimensionality.c
sexp* export_rray_dimensionality(sexp* x);

// dimensions.c
sexp* export_rray_dims(sexp* x);

// library.c
sexp* export_rray_init_library();

#endif
