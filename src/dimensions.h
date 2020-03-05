#ifndef RRAY_DIMENSIONS_H
#define RRAY_DIMENSIONS_H


#include "internal.h"

sexp* rray_dims(sexp* x);
sexp* rray_dims2(sexp* x, sexp* y);
sexp* rray_dims_common(sexp* xs, sexp* dims, sexp* absent);
sexp* rray_dims_expand(sexp* dims, r_ssize dimensionality);
sexp* rray_dims_split(sexp* dims, sexp* axes);
sexp* rray_dims_select(sexp* dims, sexp* axes);
sexp* rray_dims_reduce(sexp* dims, sexp* axes);
sexp* rray_as_dims(sexp* dims, const char* dims_arg);


#endif
