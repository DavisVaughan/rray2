#include "rray.h"
#include "library.h"

sexp* (*rlang_env_dots_list)(sexp*) = NULL;

void rray_init_rlang() {
  rlang_env_dots_list = (sexp* (*)(sexp*)) R_GetCCallable("rlang", "rlang_env_dots_list");
}
