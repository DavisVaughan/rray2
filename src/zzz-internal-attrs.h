#ifndef RRAY_INTERNAL_ATTRS_H
#define RRAY_INTERNAL_ATTRS_H

#include "zzz-internal-r.h"
#include "zzz-internal-sym.h"

sexp* r_get_attribute(sexp* x, sexp* tag);

static inline sexp* r_get_attributes(sexp* x) {
  return ATTRIB(x);
}

static inline sexp* r_get_dims(sexp* x) {
  return r_get_attribute(x, r_sym_dim);
}
static inline sexp* r_get_dimnames(sexp* x) {
  return r_get_attribute(x, r_sym_dimnames);
}


static inline void r_poke_attribute(sexp* x, sexp* tag, sexp* value) {
  Rf_setAttrib(x, tag, value);
}

static inline void r_poke_dims(sexp* x, sexp* dims) {
  r_poke_attribute(x, r_sym_dim, dims);
}


#endif
