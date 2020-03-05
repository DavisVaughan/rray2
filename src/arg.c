#include "rray.h"

const char* rray_as_arg(sexp* arg, const char* arg_arg) {
  if (r_typeof(arg) != r_type_character) {
    r_abort("`%s` must be a character vector, not %s", arg_arg, r_sexp_as_friendly_c_string(arg));
  }

  if (r_length(arg) != 1) {
    r_abort("`%s` must have length 1, not %i", arg_arg, r_length(arg));
  }

  return r_chr_get_c_string(arg, 0);
}
