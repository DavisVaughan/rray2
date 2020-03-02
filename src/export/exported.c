#include <rray.h>

// library.c

sexp* export_rray_init_library() {
  rray_init_library();
  return r_null;
}
