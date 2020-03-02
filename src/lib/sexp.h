#ifndef RRAY_SEXP_H
#define RRAY_SEXP_H

#include "r.h"

static inline r_ssize r_length(sexp* x) {
  return Rf_xlength(x);
}

static inline enum r_type r_typeof(sexp* x) {
  return TYPEOF(x);
}

#endif
