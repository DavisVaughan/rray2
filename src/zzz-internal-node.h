#ifndef RRAY_NODE_H
#define RRAY_NODE_H

#include "zzz-internal-r.h"

static inline sexp* r_node_car(sexp* x) {
  return CAR(x);
}
static inline sexp* r_node_cdr(sexp* x) {
  return CDR(x);
}
static inline sexp* r_node_caar(sexp* x) {
  return CAAR(x);
}
static inline sexp* r_node_cadr(sexp* x) {
  return CADR(x);
}
static inline sexp* r_node_cdar(sexp* x) {
  return CDAR(x);
}
static inline sexp* r_node_cddr(sexp* x) {
  return CDDR(x);
}
static inline sexp* r_node_tail(sexp* x) {
  while (CDR(x) != r_null) {
    x = CDR(x);
  }
  return x;
}

static inline void r_node_poke_car(sexp* x, sexp* replacement) {
  SETCAR(x, replacement);
}
static inline void r_node_poke_cdr(sexp* x, sexp* replacement) {
  SETCDR(x, replacement);
}
static inline void r_node_poke_caar(sexp* x, sexp* replacement) {
  SETCAR(CAR(x), replacement);
}
static inline void r_node_poke_cadr(sexp* x, sexp* replacement) {
  SETCADR(x, replacement);
}
static inline void r_node_poke_cdar(sexp* x, sexp* replacement) {
  SETCDR(CAR(x), replacement);
}
static inline void r_node_poke_cddr(sexp* x, sexp* replacement) {
  SETCDR(CDR(x), replacement);
}

static inline sexp* r_node_tag(sexp* x) {
  return TAG(x);
}
static inline void r_node_poke_tag(sexp* x, sexp* tag) {
  SET_TAG(x, tag);
}

#endif
