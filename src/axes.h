#ifndef RRAY_AXES_H
#define RRAY_AXES_H


#include "internal.h"

sexp* rray_as_axes(sexp* axes, r_ssize dimensionality);
sexp* rray_axes_complement(sexp* axes, r_ssize dimensionality);

#endif
