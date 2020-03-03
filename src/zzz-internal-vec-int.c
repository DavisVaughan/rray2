#include "zzz-internal-sexp.h"
#include "zzz-internal-library.h"

#include "zzz-internal-vec-int.h"

sexp* rray_shared_empty_int = NULL;
sexp* rray_shared_zero_int = NULL;

void rray_init_internal_vec_int() {
  rray_shared_empty_int = r_new_int(0);
  r_mark_precious(rray_shared_empty_int);
  r_mark_shared(rray_shared_empty_int);

  rray_shared_zero_int = r_scalar_int(0);
  r_mark_precious(rray_shared_zero_int);
  r_mark_shared(rray_shared_zero_int);
}
