#include "library.h"
#include "zzz-internal-library.h"

void rray_init_internal() {
  rray_init_internal_vec_int();
}

void rray_init_library() {
  rray_init_internal();
  rray_init_rlang();
  rray_init_vctrs();
}
