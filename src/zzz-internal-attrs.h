#ifndef RRAY_ATTRS_H
#define RRAY_ATTRS_H

#include "zzz-internal-r.h"
#include "zzz-internal-sym.h"

sexp* r_get_attribute(sexp* x, sexp* tag);

static inline sexp* r_get_attributes(sexp* x) {
  return ATTRIB(x);
}

static inline sexp* r_get_dim(sexp* x) {
  return r_get_attribute(x, r_sym_dim);
}
static inline sexp* r_get_dimnames(sexp* x) {
  return r_get_attribute(x, r_sym_dimnames);
}


#endif
