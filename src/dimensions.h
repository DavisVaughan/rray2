#ifndef RRAY_DIMENSIONS_H
#define RRAY_DIMENSIONS_H


#include "internal.h"

sexp* rray_dims(sexp* x);
sexp* rray_dims2(sexp* x, sexp* y);
sexp* rray_dims_common(sexp* xs, sexp* dims, sexp* absent);
sexp* rray_dims_expand(sexp* dims, r_ssize dimensionality);
sexp* rray_dims_split(sexp* dims, sexp* axes);
sexp* rray_as_dims(sexp* dims);


static inline r_ssize rray_axis2(r_ssize axis, r_ssize x_dim, r_ssize y_dim) {
  if (x_dim == y_dim) {
    return x_dim;
  } else if (x_dim == 1) {
    return y_dim;
  } else if (y_dim == 1) {
    return x_dim;
  } else {
    r_abort("Dimensions along axis %td cannot be broadcast: %td, %td.", axis, x_dim, y_dim);
  }
}

#endif
