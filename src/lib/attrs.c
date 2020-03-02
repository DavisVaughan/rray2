#include "rray.h"

// Unlike Rf_getAttrib(), this never allocates
sexp* r_get_attribute(sexp* x, sexp* tag) {
  sexp* attrs = r_get_attributes(x);

  while (attrs != r_null) {
    if (r_node_tag(attrs) == tag) {
      sexp* attr = r_node_car(attrs);
      r_mark_shared(attr);
      return attr;
    }
    attrs = r_node_cdr(attrs);
  }

  return r_null;
}
