#include <vctrs.c>
#include "zzz-internal-r.h"
#include "zzz-internal-library.h"

#include "zzz-internal-vctrs.h"

sexp* (*vec_cast)(sexp*, sexp*) = NULL;

void rray_init_internal_vctrs() {
  vctrs_init_api();

  vec_cast = (sexp* (*)(sexp*, sexp*)) R_GetCCallable("vctrs", "exp_vec_cast");
}
