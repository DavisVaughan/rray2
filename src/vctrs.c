#include "rray.h"
#include "library.h"
#include <vctrs.c>

sexp* (*vec_cast)(sexp*, sexp*) = NULL;

void rray_init_vctrs() {
  vctrs_init_api();

  vec_cast = (sexp* (*)(sexp*, sexp*)) R_GetCCallable("vctrs", "exp_vec_cast");
}
