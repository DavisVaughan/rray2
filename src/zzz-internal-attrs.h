#ifndef RRAY_ATTRS_H
#define RRAY_ATTRS_H

#include "zzz-internal-r.h"

sexp* r_get_attribute(sexp* x, sexp* tag);

static inline sexp* r_get_attributes(sexp* x) {
  return ATTRIB(x);
}


#endif
