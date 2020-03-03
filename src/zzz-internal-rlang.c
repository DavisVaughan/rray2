#include "zzz-internal-r.h"
#include "zzz-internal-library.h"

#include "zzz-internal-rlang.h"

sexp* (*rlang_env_dots_list)(sexp*) = NULL;

void rray_init_internal_rlang() {
  rlang_env_dots_list = (sexp* (*)(sexp*)) R_GetCCallable("rlang", "rlang_env_dots_list");
}
